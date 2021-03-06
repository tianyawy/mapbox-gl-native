#include <mbgl/map/vector_tile.hpp>
#include <mbgl/style/filter_expression_private.hpp>

#include <algorithm>
#include <iostream>

using namespace mbgl;


std::ostream& mbgl::operator<<(std::ostream& os, const FeatureType& type) {
    switch (type) {
        case FeatureType::Unknown: return os << "Unknown";
        case FeatureType::Point: return os << "Point";
        case FeatureType::LineString: return os << "LineString";
        case FeatureType::Polygon: return os << "Polygon";
        default: return os << "Invalid";
    }
}

VectorTileFeature::VectorTileFeature(pbf feature, const VectorTileLayer& layer) {
    while (feature.next()) {
        if (feature.tag == 1) { // id
            id = feature.varint<uint64_t>();
        } else if (feature.tag == 2) { // tags
            // tags are packed varints. They should have an even length.
            pbf tags = feature.message();
            while (tags) {
                uint32_t tag_key = tags.varint();

                if (layer.keys.size() <= tag_key) {
                    throw std::runtime_error("feature referenced out of range key");
                }

                if (tags) {
                    uint32_t tag_val = tags.varint();
                    if (layer.values.size() <= tag_val) {
                        throw std::runtime_error("feature referenced out of range value");
                    }

                    properties.emplace(layer.keys[tag_key], layer.values[tag_val]);
                } else {
                    throw std::runtime_error("uneven number of feature tag ids");
                }
            }
        } else if (feature.tag == 3) { // type
            type = (FeatureType)feature.varint();
        } else if (feature.tag == 4) { // geometry
            geometry = feature.message();
        } else {
            feature.skip();
        }
    }
}


std::ostream& mbgl::operator<<(std::ostream& os, const VectorTileFeature& feature) {
    os << "Feature(" << feature.id << "): " << feature.type << std::endl;
    for (const auto& prop : feature.properties) {
        os << "  - " << prop.first << ": " << prop.second << std::endl;
    }
    return os;
}


VectorTile::VectorTile() {}


VectorTile::VectorTile(pbf tile) {
    while (tile.next()) {
        if (tile.tag == 3) { // layer
            VectorTileLayer layer(tile.message());
            layers.emplace(layer.name, std::forward<VectorTileLayer>(layer));
        } else {
            tile.skip();
        }
    }
}

VectorTile& VectorTile::operator=(VectorTile && other) {
    if (this != &other) {
        layers.swap(other.layers);
    }
    return *this;
}

VectorTileLayer::VectorTileLayer(pbf layer) : data(layer) {
    std::vector<std::string> stacks;

    while (layer.next()) {
        if (layer.tag == 1) { // name
            name = layer.string();
        } else if (layer.tag == 3) { // keys
            keys.emplace_back(layer.string());
            key_index.emplace(keys.back(), keys.size() - 1);
        } else if (layer.tag == 4) { // values
            values.emplace_back(std::move(parseValue(layer.message())));
        } else if (layer.tag == 5) { // extent
            extent = layer.varint();
        } else {
            layer.skip();
        }
    }
}

FilteredVectorTileLayer::FilteredVectorTileLayer(const VectorTileLayer& layer_, const FilterExpression &filterExpression_)
    : layer(layer_),
      filterExpression(filterExpression_) {
}

FilteredVectorTileLayer::iterator FilteredVectorTileLayer::begin() const {
    return iterator(*this, layer.data);
}

FilteredVectorTileLayer::iterator FilteredVectorTileLayer::end() const {
    return iterator(*this, pbf(layer.data.end, 0));
}

FilteredVectorTileLayer::iterator::iterator(const FilteredVectorTileLayer& parent_, const pbf& data_)
    : parent(parent_),
      feature(pbf()),
      data(data_) {
    operator++();
}

VectorTileTagExtractor::VectorTileTagExtractor(const VectorTileLayer &layer) : layer_(layer) {}


void VectorTileTagExtractor::setTags(const pbf &pbf) {
    tags_ = pbf;
}

mapbox::util::optional<Value> VectorTileTagExtractor::getValue(const std::string &key) const {
    if (key == "$type") {
        return Value(uint64_t(type_));
    }

    mapbox::util::optional<Value> value;

    auto field_it = layer_.key_index.find(key);
    if (field_it != layer_.key_index.end()) {
        const uint32_t filter_key = field_it->second;

        // Now loop through all the key/value pair tags.
        // tags are packed varints. They should have an even length.
        pbf tags_pbf = tags_;
        uint32_t tag_key, tag_val;
        while (tags_pbf) {
            tag_key = tags_pbf.varint();
            if (!tags_pbf) {
                // This should not happen; otherwise the vector tile is invalid.
                fprintf(stderr, "[WARNING] uneven number of feature tag ids\n");
                return value;
            }
            // Note: We need to run this command in all cases, even if the keys don't match.
            tag_val = tags_pbf.varint();

            if (tag_key == filter_key) {
                if (layer_.values.size() > tag_val) {
                    value = layer_.values[tag_val];
                } else {
                    fprintf(stderr, "[WARNING] feature references out of range value\n");
                    break;
                }
            }
        }
    }

    return value;
}

void VectorTileTagExtractor::setType(FeatureType type) {
    type_ = type;
}

template bool mbgl::evaluate(const FilterExpression&, const VectorTileTagExtractor&);

void FilteredVectorTileLayer::iterator::operator++() {
    valid = false;

    const FilterExpression &expression = parent.filterExpression;

    while (data.next(2)) { // feature
        feature = data.message();
        pbf feature_pbf = feature;

        VectorTileTagExtractor extractor(parent.layer);

        // Retrieve the basic information
        while (feature_pbf.next()) {
            if (feature_pbf.tag == 2) { // tags
                extractor.setTags(feature_pbf.message());
            } else if (feature_pbf.tag == 3) { // geometry type
                extractor.setType(FeatureType(feature_pbf.varint()));
            } else {
                feature_pbf.skip();
            }
        }

        if (evaluate(expression, extractor)) {
            valid = true;
            return; // data loop
        } else {
            valid = false;
        }
    }
}

bool FilteredVectorTileLayer::iterator::operator!=(const iterator& other) const {
    return !(data.data == other.data.data && data.end == other.data.end && valid == other.valid);
}

const pbf& FilteredVectorTileLayer::iterator:: operator*() const {
    return feature;
}
