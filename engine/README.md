# Engine

2D top-down engine

## Various Notes
```c
// 0 degrees rotation means the object is oriented right as trigonometry standard
// clockwise rotation is used:
// https://en.wikipedia.org/wiki/Rotation_matrix#Non-standard_orientation_of_the_coordinate_system
// TODO: separate game_object (representing a static object) from movible_object (extension of game_object)
//  - add another rotation field in movible_object that conforms to what's written above
//  - the rotation in game_object can be used to render the object in the right direction
//      i.e if the bitmap image is oriented south, a -90 degree rotation can 
//          be set to match initial 0 degree movible_object rotation.
//          Equally, let the image face south but then set movible_object rotation to 90

// struct inheritance 
// http://www.deleveld.dds.nl/inherit.htm

//texture properties
//https://github.com/libsdl-org/SDL/blob/main/include/SDL3/SDL_render.h#L654
//
//#define SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER           "colorspace"
//#define SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER               "format"
//#define SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER               "access"
//#define SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER                "width"
//#define SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER               "height"
//#define SDL_PROP_TEXTURE_CREATE_SDR_WHITE_POINT_FLOAT       "SDR_white_point"
//#define SDL_PROP_TEXTURE_CREATE_HDR_HEADROOM_FLOAT          "HDR_headroom"
//#define SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_POINTER       "d3d11.texture"
//#define SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_U_POINTER     "d3d11.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_V_POINTER     "d3d11.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_D3D12_TEXTURE_POINTER       "d3d12.texture"
//#define SDL_PROP_TEXTURE_CREATE_D3D12_TEXTURE_U_POINTER     "d3d12.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_D3D12_TEXTURE_V_POINTER     "d3d12.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_METAL_PIXELBUFFER_POINTER   "metal.pixelbuffer"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_NUMBER       "opengl.texture"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_UV_NUMBER    "opengl.texture_uv"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_U_NUMBER     "opengl.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_OPENGL_TEXTURE_V_NUMBER     "opengl.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_NUMBER    "opengles2.texture"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_UV_NUMBER "opengles2.texture_uv"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_U_NUMBER  "opengles2.texture_u"
//#define SDL_PROP_TEXTURE_CREATE_OPENGLES2_TEXTURE_V_NUMBER  "opengles2.texture_v"
//#define SDL_PROP_TEXTURE_CREATE_VULKAN_TEXTURE_NUMBER       "vulkan.texture"

//texture->magic = &SDL_texture_magic;
//texture->colorspace = (SDL_Colorspace)SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, default_colorspace);
//texture->format = format;
//texture->access = access;
//texture->w = w;
//texture->h = h;
//texture->color.r = 1.0f;
//texture->color.g = 1.0f;
//texture->color.b = 1.0f;
//texture->color.a = 1.0f;
//texture->scaleMode = SDL_SCALEMODE_LINEAR;
//texture->view.pixel_w = w;
//texture->view.pixel_h = h;
//texture->view.viewport.w = -1;
//texture->view.viewport.h = -1;
//texture->view.scale.x = 1.0f;
//texture->view.scale.y = 1.0f;
//texture->renderer = renderer;
//texture->next = renderer->textures;
```
