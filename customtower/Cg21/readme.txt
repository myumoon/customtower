NVIDIA Cg 2.0 May 2008 README  Copyright (C) 2002-2008 NVIDIA Corp.
=============================

This distribution contains
--------------------------

- NVIDIA Cg toolkit documentation
  in the docs directory
     
- NVIDIA Cg compiler (cgc)
  in the bin directory

- NVIDIA Cg runtime libraries
  in the lib directory

- Example Cg applications
  in the examples directory

- Under Microsoft Windows, a Cg language syntax highlighter
  for Microsoft Visual Studio is provided in the
  msdev_syntax_highlighting directory

- Under Microsoft Windows, if selected at install time, 64-bit
  binaries and libraries are in the bin.x64 and lib.x64 directories.

See the release notes (docs/CgReleaseNotes.pdf) for detailed
information about this release.

The Cg toolkit is available for a number of different hardware and
OS platforms.  As of this writing, supported platforms include:

  - Microsoft NT 4, 2000, and Windows XP on IA32/x86/x86-64 (Intel, AMD)
  - Linux on IA32/x86 (Intel, AMD)
  - Linux for x64 (AMD64 and EMT64)
  - MacOS X (Tiger and Leopard)
  - Solaris (x86)

Visit the NVIDIA Cg website at http://developer.nvidia.com/page/cg_main.html
for updates and complete compatibility information.

Changes since Cg 2.0 January 2008
---------------------------------
- New features
  - Many performance improvements
  - Bug fixes
    - Added support for samplerBUF to the runtime
    - Allow 'Texture' as a variable name
    - Fixed a bug in setting and getting string annotation values
    - Fixed a crash at exit when running on 64-bit Windows
    - Fixed a problem with cgGLSetOptimalOptions on the GPU Program4 profiles
    - Fixed a problem with using 'discard' on MacOS
- New examples
  - OpenGL/basic/22_specular_bump_map
  - OpenGL/basic/26_toon_shading
  - OpenGL/basic/27_projective_texturing

Changes since Dec. 2007
-----------------------
- New features
  - The HLSL profiles can now run on SM2.0 and SM2.x hardware
  - Fixed a multitexture sampler configuration bug with GLSL profiles in CgFX
  - Fixed problems with using buffer semantics on pre-G80 class GPUs
  - The set and get parameter routines now silently ignore "extra" components.
    For example, if cgSetParameter4f is used to send 4 values to a CG_FLOAT2
    parameter, the first two values are used but the last two are ignored.
  - Added support for OSX x86_64
  - Fixed a bug with the path variable after installing Windows 64-bit dlls
- New documentation
  - Added a new section on cgc
  - Completed the gp4 profile documentation
  - Other general improvements

Changes since Cg 1.5
--------------------
- New features
  - OpenGL GPU Program4 profiles
  - HLSL9 translation profiles
  - Geometry programs
  - Constant buffers
  - Texture arrays
  - True integer data types
  - Performance improvements
- New examples
  - OpenGL/advanced/buffer_lighting
  - OpenGL/advanced/cgfx_boxfilter
  - OpenGL/advanced/cgfx_texture_array
  - OpenGL/advanced/custom_state_assignments
  - OpenGL/advanced/gs_interp_quad
  - OpenGL/advanced/gs_md2render
  - OpenGL/advanced/gs_quadnormal
  - OpenGL/advanced/gs_shrinky
  - OpenGL/advanced/gs_simple
  - OpenGL/advanced/interpolation_modifier
  - OpenGL/advanced/texture_array
  - OpenGL/advanced/vertex_texture
  - OpenGL/basic/18_cube_map_reflection
  - OpenGL/basic/19_cube_map_refraction
  - OpenGL/basic/20_chromatic_dispersion
  - OpenGL/basic/21_bump_map_wall
  - OpenGL/basic/25_uniform_fog
- New documentation
  - New Cg Language Specification
  - Updated profile reference pages
