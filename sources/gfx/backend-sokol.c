#if defined(RAYFORK_GRAPHICS_BACKEND_DIRECTX) || defined(RAYFORK_GRAPHICS_BACKEND_METAL)
#include "rayfork-backend-sokol.h"

#define SOKOL_IMPL
#if defined(RAYFORK_GRAPHICS_BACKEND_DIRECTX)
#define SOKOL_D3D11
#elif defined(RAYFORK_GRAPHICS_BACKEND_METAL)
#define SOKOL_METAL
#endif
#include "sokol_gfx.h"

rf_internal void rf__gfx_backend_internal_init(rf_gfx_backend_data* gfx_data);

#pragma region shader

// Load default shader (just vertex positioning and texture coloring). Note: This shader program is used for internal buffers
RF_API rf_shader rf_load_default_shader();

// Load shader from code strings. If shader string is NULL, using default vertex/fragment shaders
RF_API rf_shader rf_gfx_load_shader(const char* vs_code, const char* fs_code);

// Unload shader from GPU memory (VRAM)
RF_API void rf_gfx_unload_shader(rf_shader shader);

// Get shader uniform location
RF_API int rf_gfx_get_shader_location(rf_shader shader, const char* uniform_name);

// Set shader uniform value
RF_API void rf_gfx_set_shader_value(rf_shader shader, int uniform_loc, const void* value, int uniform_name);

// Set shader uniform value vector
RF_API void rf_gfx_set_shader_value_v(rf_shader shader, int uniform_loc, const void* value, int uniform_name, int count);

// Set shader uniform value (matrix 4x4)
RF_API void rf_gfx_set_shader_value_matrix(rf_shader shader, int uniform_loc, rf_mat mat);

// Set shader uniform value for texture
RF_API void rf_gfx_set_shader_value_texture(rf_shader shader, int uniform_loc, rf_texture2d texture);

// Return internal rf_ctx->gl_ctx.projection matrix
RF_API rf_mat rf_gfx_get_matrix_projection();

// Return internal rf_ctx->gl_ctx.modelview matrix
RF_API rf_mat rf_gfx_get_matrix_modelview();

// Set a custom projection matrix (replaces internal rf_ctx->gl_ctx.projection matrix)
RF_API void rf_gfx_set_matrix_projection(rf_mat proj);

// Set a custom rf_ctx->gl_ctx.modelview matrix (replaces internal rf_ctx->gl_ctx.modelview matrix)
RF_API void rf_gfx_set_matrix_modelview(rf_mat view);

#pragma endregion

#pragma region rf_gfx

// Choose the blending mode (alpha, additive, multiplied)
RF_API void rf_gfx_blend_mode(rf_blend_mode mode);

// Choose the current matrix to be transformed
RF_API void rf_gfx_matrix_mode(rf_matrix_mode mode);

// Push the current matrix into rf_ctx->gl_ctx.stack
RF_API void rf_gfx_push_matrix();

// Pop lattest inserted matrix from rf_ctx->gl_ctx.stack
RF_API void rf_gfx_pop_matrix();

// Reset current matrix to identity matrix
RF_API void rf_gfx_load_identity();

// Multiply the current matrix by a translation matrix
RF_API void rf_gfx_translatef(float x, float y, float z);

// Multiply the current matrix by a rotation matrix
RF_API void rf_gfx_rotatef(float angleDeg, float x, float y, float z);

// Multiply the current matrix by a scaling matrix
RF_API void rf_gfx_scalef(float x, float y, float z);

// Multiply the current matrix by another matrix
RF_API void rf_gfx_mult_matrixf(float* matf);

// Multiply the current matrix by a perspective matrix generated by parameters
RF_API void rf_gfx_frustum(double left, double right, double bottom, double top, double znear, double zfar);

// Multiply the current matrix by an orthographic matrix generated by parameters
RF_API void rf_gfx_ortho(double left, double right, double bottom, double top, double znear, double zfar);

// Set the viewport area (transformation from normalized device coordinates to window coordinates)
void rf_gfx_viewport(int x, int y, int width, int height);

// Initialize drawing mode (how to organize vertex)
RF_API void rf_gfx_begin(rf_drawing_mode mode);

// Finish vertex providing
RF_API void rf_gfx_end();

// Define one vertex (position)
RF_API void rf_gfx_vertex2i(int x, int y);

// Define one vertex (position)
RF_API void rf_gfx_vertex2f(float x, float y);

// Define one vertex (position)
// NOTE: Vertex position data is the basic information required for drawing
RF_API void rf_gfx_vertex3f(float x, float y, float z);

// Define one vertex (texture coordinate)
// NOTE: rf_texture coordinates are limited to QUADS only
RF_API void rf_gfx_tex_coord2f(float x, float y);

// Define one vertex (normal)
// NOTE: Normals limited to TRIANGLES only?
RF_API void rf_gfx_normal3f(float x, float y, float z);

// Define one vertex (color)
RF_API void rf_gfx_color3f(float x, float y, float z);

// Define one vertex (color)
RF_API void rf_gfx_color4ub(unsigned char x, unsigned char y, unsigned char z, unsigned char w);

// Define one vertex (color)
RF_API void rf_gfx_color4f(float r, float g, float b, float a);

// Enable texture usage
RF_API void rf_gfx_enable_texture(unsigned int id);

// Disable texture usage
RF_API void rf_gfx_disable_texture();

// Set texture parameters (wrap mode/filter mode)
RF_API void rf_gfx_set_texture_wrap(rf_texture2d texture, rf_texture_wrap_mode wrap_mode);

// Set filter for texture
RF_API void rf_gfx_set_texture_filter(rf_texture2d texture, rf_texture_filter_mode filter_mode);

// Enable rendering to texture (fbo)
RF_API void rf_gfx_enable_render_texture(unsigned int id);

// Disable rendering to texture
RF_API void rf_gfx_disable_render_texture(void);

// Enable depth test
RF_API void rf_gfx_enable_depth_test(void);

// Disable depth test
RF_API void rf_gfx_disable_depth_test(void);

// Enable backface culling
RF_API void rf_gfx_enable_backface_culling(void);

// Disable backface culling
RF_API void rf_gfx_disable_backface_culling(void);

// Enable scissor test
RF_API void rf_gfx_enable_scissor_test(void);

// Disable scissor test
RF_API void rf_gfx_disable_scissor_test(void);

// Scissor test
RF_API void rf_gfx_scissor(int x, int y, int width, int height);

// Enable wire mode
RF_API void rf_gfx_enable_wire_mode(void);

// Disable wire mode
RF_API void rf_gfx_disable_wire_mode(void);

// Unload texture from GPU memory
RF_API void rf_gfx_delete_textures(unsigned int id);

// Unload render texture from GPU memory
RF_API void rf_gfx_delete_render_textures(rf_render_texture2d target);

// Unload shader from GPU memory
RF_API void rf_gfx_delete_shader(unsigned int id);

// Unload vertex data (VAO) from GPU memory
RF_API void rf_gfx_delete_vertex_arrays(unsigned int id);

// Unload vertex data (VBO) from GPU memory
RF_API void rf_gfx_delete_buffers(unsigned int id);

// Clear color buffer with color
RF_API void rf_gfx_clear_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

// Clear used screen buffers (color and depth)
RF_API void rf_gfx_clear_screen_buffers(void);

// Update GPU buffer with new data
RF_API void rf_gfx_update_buffer(int buffer_id, void* data, int data_size);

// Load a new attributes buffer
RF_API unsigned int rf_gfx_load_attrib_buffer(unsigned int vao_id, int shader_loc, void* buffer, int size, rf_bool dynamic);

RF_API void rf_gfx_init_vertex_buffer(rf_vertex_buffer* vertex_buffer);

// Vertex Buffer Object deinitialization (memory free)
RF_API void rf_gfx_close();

// Update and draw internal buffers
RF_API void rf_gfx_draw();

// Check internal buffer overflow for a given number of vertex
RF_API rf_bool rf_gfx_check_buffer_limit(int v_count);

// Set debug marker
RF_API void rf_gfx_set_debug_marker(const char* text);

// Convert image data to OpenGL texture (returns OpenGL valid Id)
RF_API unsigned int rf_gfx_load_texture(void* data, int width, int height, rf_pixel_format format, int mipmap_count);

// Load depth texture/renderbuffer (to be attached to fbo)
// WARNING: OpenGL ES 2.0 requires GL_OES_depth_texture/WEBGL_depth_texture extensions
RF_API unsigned int rf_gfx_load_texture_depth(int width, int height, int bits, rf_bool use_render_buffer);

// Load texture cubemap
// NOTE: Cubemap data is expected to be 6 images in a single column,
// expected the following convention: +X, -X, +Y, -Y, +Z, -Z
RF_API unsigned int rf_gfx_load_texture_cubemap(void* data, int size, rf_pixel_format format);

// Update already loaded texture in GPU with new data
// NOTE: We don't know safely if internal texture format is the expected one...
RF_API void rf_gfx_update_texture(unsigned int id, int width, int height, rf_pixel_format format, const void* pixels, int pixels_size);

// Get OpenGL internal formats and data type from raylib rf_pixel_format
RF_API rf_gfx_pixel_format rf_gfx_get_internal_texture_formats(rf_pixel_format format);

// Unload texture from GPU memory
RF_API void rf_gfx_unload_texture(unsigned int id);

// Generate mipmap data for selected texture
RF_API void rf_gfx_generate_mipmaps(rf_texture2d* texture);

// Read texture pixel data
RF_API rf_image rf_gfx_read_texture_pixels_to_buffer(rf_texture2d texture, void* dst, int dst_size);

RF_API rf_image rf_gfx_read_texture_pixels(rf_texture2d texture, rf_allocator allocator);

// Read screen pixel data (color buffer)
RF_API void rf_gfx_read_screen_pixels(rf_color* dst, int width, int height);

// Load a texture to be used for rendering (fbo with default color and depth attachments)
// NOTE: If colorFormat or depth_bits are no supported, no attachment is done
RF_API rf_render_texture2d rf_gfx_load_render_texture(int width, int height, rf_pixel_format format, int depth_bits, rf_bool use_depth_texture);

// Attach color buffer texture to an fbo (unloads previous attachment)
// NOTE: Attach type: 0-rf_color, 1-Depth renderbuffer, 2-Depth texture
RF_API void rf_gfx_render_texture_attach(rf_render_texture2d target, unsigned int id, int attach_type);

// Verify render texture is complete
RF_API rf_bool rf_gfx_render_texture_complete(rf_render_texture2d target);

// Upload vertex data into a VAO (if supported) and VBO
RF_API void rf_gfx_load_mesh(rf_mesh* mesh, rf_bool dynamic);

// Update vertex or index data on GPU (upload new data to one buffer)
RF_API void rf_gfx_update_mesh(rf_mesh mesh, int buffer, int num);

// Update vertex or index data on GPU, at index
// WARNING: error checking is in place that will cause the data to not be
//          updated if offset + size exceeds what the buffer can hold
RF_API void rf_gfx_update_mesh_at(rf_mesh mesh, int buffer, int num, int index);

// Draw a 3d mesh with material and transform
RF_API void rf_gfx_draw_mesh(rf_mesh mesh, rf_material material, rf_mat transform);

// Unload mesh data from the GPU
RF_API void rf_gfx_unload_mesh(rf_mesh mesh);

#pragma endregion

#pragma region gen textures

// Generate cubemap texture from HDR texture
RF_API rf_texture2d rf_gen_texture_cubemap(rf_shader shader, rf_texture2d sky_hdr, rf_int size);

// Generate irradiance texture using cubemap data
RF_API rf_texture2d rf_gen_texture_irradiance(rf_shader shader, rf_texture2d cubemap, rf_int size);

// Generate prefilter texture using cubemap data
RF_API rf_texture2d rf_gen_texture_prefilter(rf_shader shader, rf_texture2d cubemap, rf_int size);

// Generate BRDF texture using cubemap data. Todo: Review implementation: https://github.com/HectorMF/BRDFGenerator
RF_API rf_texture2d rf_gen_texture_brdf(rf_shader shader, rf_int size);

#pragma endregion

#endif