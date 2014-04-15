// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.
#include <llmr/platform/gl.hpp>
#ifdef GL_ES_VERSION_2_0
#include <llmr/shader/shaders.hpp>

using namespace llmr;

const shader_source llmr::shaders[SHADER_COUNT] = {
   {
       "precision highp float;\nattribute vec2 a_pos;\nattribute vec2 a_extrude;\nuniform mat4 u_matrix;\nuniform mat4 u_exmatrix;\nuniform vec2 u_linewidth;\nvarying vec2 v_normal;\nvoid main ()\n{\n  vec2 normal_1;\n  vec2 tmpvar_2;\n  tmpvar_2 = (vec2(mod (a_pos, 2.0)));\n  normal_1.x = tmpvar_2.x;\n  normal_1.y = sign((tmpvar_2.y - 0.5));\n  v_normal = normal_1;\n  vec4 tmpvar_3;\n  tmpvar_3.zw = vec2(0.0, 0.0);\n  tmpvar_3.xy = ((u_linewidth.x * a_extrude) * 0.015873);\n  vec4 tmpvar_4;\n  tmpvar_4.zw = vec2(0.0, 1.0);\n  tmpvar_4.xy = floor((a_pos * 0.5));\n  gl_Position = ((u_matrix * tmpvar_4) + (u_exmatrix * tmpvar_3));\n}\n\n",
       "precision highp float;\nuniform vec2 u_linewidth;\nuniform vec4 u_color;\nvarying vec2 v_normal;\nvoid main ()\n{\n  float tmpvar_1;\n  tmpvar_1 = (sqrt(dot (v_normal, v_normal)) * u_linewidth.x);\n  gl_FragColor = (u_color * clamp (min (\n    (tmpvar_1 - (u_linewidth.y - 1.0))\n  , \n    (u_linewidth.x - tmpvar_1)\n  ), 0.0, 1.0));\n}\n\n",
   },
   {
       "precision highp float;\nattribute vec2 a_pos;\nuniform mat4 u_matrix;\nuniform vec2 u_world;\nuniform float u_size;\nvarying highp vec2 v_pos;\nvoid main ()\n{\n  vec4 tmpvar_1;\n  tmpvar_1.zw = vec2(0.0, 1.0);\n  tmpvar_1.xy = floor((a_pos / 2.0));\n  vec4 tmpvar_2;\n  tmpvar_2 = (u_matrix * tmpvar_1);\n  gl_Position = tmpvar_2;\n  v_pos = ((tmpvar_2.xy + 1.0) * u_world);\n  gl_PointSize = u_size;\n}\n\n",
       "precision highp float;\nuniform vec4 u_color;\nuniform vec2 u_linewidth;\nvarying vec2 v_pos;\nvoid main ()\n{\n  highp float tmpvar_1;\n  highp vec2 x_2;\n  x_2 = (v_pos - gl_FragCoord.xy);\n  tmpvar_1 = sqrt(dot (x_2, x_2));\n  highp vec4 tmpvar_3;\n  tmpvar_3 = (u_color * clamp (min (\n    (tmpvar_1 - (u_linewidth.y - 1.0))\n  , \n    (u_linewidth.x - tmpvar_1)\n  ), 0.0, 1.0));\n  gl_FragColor = tmpvar_3;\n}\n\n",
   },
   {
       "precision highp float;\nattribute vec2 a_pos;\nuniform mat4 u_matrix;\nuniform vec2 u_world;\nvarying highp vec2 v_pos;\nvoid main ()\n{\n  vec4 tmpvar_1;\n  tmpvar_1.zw = vec2(0.0, 1.0);\n  tmpvar_1.xy = a_pos;\n  vec4 tmpvar_2;\n  tmpvar_2 = (u_matrix * tmpvar_1);\n  gl_Position = tmpvar_2;\n  v_pos = (((tmpvar_2.xy + 1.0) / 2.0) * u_world);\n}\n\n",
       "precision highp float;\nuniform vec4 u_color;\nvarying vec2 v_pos;\nvoid main ()\n{\n  highp vec2 x_1;\n  x_1 = (v_pos - gl_FragCoord.xy);\n  highp float tmpvar_2;\n  tmpvar_2 = clamp (((\n    sqrt(dot (x_1, x_1))\n   - 1.0) / -1.0), 0.0, 1.0);\n  highp vec4 tmpvar_3;\n  tmpvar_3 = (u_color * (tmpvar_2 * (tmpvar_2 * \n    (3.0 - (2.0 * tmpvar_2))\n  )));\n  gl_FragColor = tmpvar_3;\n}\n\n",
   },
   {
       "precision highp float;\nuniform mat4 u_matrix;\nattribute vec2 a_pos;\nvarying vec2 v_pos;\nvoid main ()\n{\n  v_pos = a_pos;\n  vec4 tmpvar_1;\n  tmpvar_1.zw = vec2(0.0, 1.0);\n  tmpvar_1.xy = a_pos;\n  gl_Position = (u_matrix * tmpvar_1);\n}\n\n",
       "precision highp float;\nuniform vec4 u_color;\nuniform vec2 u_offset;\nuniform vec2 u_pattern_size;\nuniform vec2 u_pattern_tl;\nuniform vec2 u_pattern_br;\nuniform float u_mix;\nuniform sampler2D u_image;\nvarying vec2 v_pos;\nvoid main ()\n{\n  vec2 tmpvar_1;\n  tmpvar_1 = (vec2(mod (((v_pos + u_offset) / u_pattern_size), 1.0)));\n  lowp vec4 tmpvar_2;\n  tmpvar_2 = mix (texture2D (u_image, mix (u_pattern_tl, u_pattern_br, tmpvar_1)), texture2D (u_image, mix (u_pattern_tl, u_pattern_br, (vec2(mod (\n    (tmpvar_1 * 2.0)\n  , 1.0))))), u_mix);\n  lowp vec4 tmpvar_3;\n  tmpvar_3 = (tmpvar_2 + (u_color * (1.0 - tmpvar_2.w)));\n  gl_FragColor = tmpvar_3;\n}\n\n",
   },
   {
       "precision highp float;\nattribute vec2 a_pos;\nuniform mat4 u_matrix;\nvoid main ()\n{\n  vec4 tmpvar_1;\n  tmpvar_1.zw = vec2(0.0, 1.0);\n  tmpvar_1.xy = a_pos;\n  gl_Position = (u_matrix * tmpvar_1);\n}\n\n",
       "precision highp float;\nuniform vec4 u_color;\nuniform float u_opacity;\nvoid main ()\n{\n  gl_FragColor = (u_color * u_opacity);\n}\n\n",
   },
   {
       "precision highp float;\nattribute vec2 a_pos;\nuniform mat4 u_matrix;\nuniform float u_size;\nvoid main ()\n{\n  vec4 tmpvar_1;\n  tmpvar_1.zw = vec2(0.0, 1.0);\n  tmpvar_1.xy = a_pos;\n  gl_Position = (u_matrix * tmpvar_1);\n  gl_PointSize = u_size;\n}\n\n",
       "precision highp float;\nuniform sampler2D u_image;\nuniform vec2 u_tl;\nuniform vec2 u_br;\nuniform vec4 u_color;\nvoid main ()\n{\n  mediump vec2 tmpvar_1;\n  tmpvar_1 = (((\n    ((gl_PointCoord * 2.0) - 1.0)\n   * 1.41421) / 2.0) + 0.5);\n  mediump vec2 tmpvar_2;\n  tmpvar_2 = mix (u_tl, u_br, tmpvar_1);\n  lowp vec4 tmpvar_3;\n  tmpvar_3 = texture2D (u_image, tmpvar_2);\n  gl_FragColor = ((tmpvar_3 * (\n    ((float((tmpvar_1.x >= 0.0)) * float((tmpvar_1.y >= 0.0))) * (1.0 - float((tmpvar_1.x >= 1.0))))\n   * \n    (1.0 - float((tmpvar_1.y >= 1.0)))\n  )) * u_color);\n}\n\n",
   },
   {
       "precision highp float;\nuniform mat4 u_matrix;\nattribute vec2 a_pos;\nvarying vec2 v_pos;\nvoid main ()\n{\n  vec4 tmpvar_1;\n  tmpvar_1.zw = vec2(0.0, 1.0);\n  tmpvar_1.xy = a_pos;\n  gl_Position = (u_matrix * tmpvar_1);\n  v_pos = (a_pos / 4096.0);\n}\n\n",
       "precision highp float;\nuniform sampler2D u_image;\nuniform float u_opacity;\nvarying vec2 v_pos;\nvoid main ()\n{\n  lowp vec4 tmpvar_1;\n  tmpvar_1 = (texture2D (u_image, v_pos) * u_opacity);\n  gl_FragColor = tmpvar_1;\n}\n\n",
   },
   {
       "precision highp float;\nattribute vec2 a_pos;\nattribute vec2 a_offset;\nattribute vec4 a_data1;\nattribute vec4 a_data2;\nuniform mat4 u_matrix;\nuniform mat4 u_exmatrix;\nuniform float u_angle;\nuniform float u_zoom;\nuniform float u_flip;\nuniform float u_fadedist;\nuniform float u_minfadezoom;\nuniform float u_maxfadezoom;\nuniform float u_fadezoom;\nuniform vec2 u_texsize;\nvarying vec2 v_tex;\nvarying float v_alpha;\nvoid main ()\n{\n  float rev_1;\n  rev_1 = 0.0;\n  float tmpvar_2;\n  tmpvar_2 = (float(mod ((a_data1.w + u_angle), 256.0)));\n  if ((((u_flip > 0.0) && (tmpvar_2 >= 64.0)) && (tmpvar_2 < 192.0))) {\n    rev_1 = 1.0;\n  };\n  float tmpvar_3;\n  tmpvar_3 = (((2.0 - \n    float((u_zoom >= a_data2.x))\n  ) - (1.0 - \n    float((u_zoom >= a_data2.y))\n  )) + rev_1);\n  float tmpvar_4;\n  tmpvar_4 = clamp (((u_fadezoom - a_data1.z) / u_fadedist), 0.0, 1.0);\n  if ((u_fadedist >= 0.0)) {\n    v_alpha = tmpvar_4;\n  } else {\n    v_alpha = (1.0 - tmpvar_4);\n  };\n  if ((u_maxfadezoom < a_data1.z)) {\n    v_alpha = 0.0;\n  };\n  if ((u_minfadezoom >= a_data1.z)) {\n    v_alpha = 1.0;\n  };\n  vec4 tmpvar_5;\n  tmpvar_5.zw = vec2(0.0, 1.0);\n  tmpvar_5.xy = a_pos;\n  vec4 tmpvar_6;\n  tmpvar_6.w = 0.0;\n  tmpvar_6.xy = (a_offset / 64.0);\n  tmpvar_6.z = ((tmpvar_3 + float(\n    (0.0 >= v_alpha)\n  )) + ((1.0 - \n    float((u_angle >= a_data2.z))\n  ) * float(\n    (u_angle >= a_data2.w)\n  )));\n  gl_Position = ((u_matrix * tmpvar_5) + (u_exmatrix * tmpvar_6));\n  v_tex = ((a_data1.xy * 4.0) / u_texsize);\n}\n\n",
       "precision highp float;\nuniform sampler2D u_texture;\nuniform vec4 u_color;\nuniform float u_buffer;\nuniform float u_gamma;\nvarying vec2 v_tex;\nvarying float v_alpha;\nvoid main ()\n{\n  float edge0_1;\n  edge0_1 = (u_buffer - u_gamma);\n  lowp float tmpvar_2;\n  tmpvar_2 = clamp (((texture2D (u_texture, v_tex).w - edge0_1) / (\n    (u_buffer + u_gamma)\n   - edge0_1)), 0.0, 1.0);\n  lowp vec4 tmpvar_3;\n  tmpvar_3 = (u_color * ((tmpvar_2 * \n    (tmpvar_2 * (3.0 - (2.0 * tmpvar_2)))\n  ) * v_alpha));\n  gl_FragColor = tmpvar_3;\n}\n\n",
   }
};
#endif