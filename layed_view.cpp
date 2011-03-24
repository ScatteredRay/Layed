// Copyright (c) 2010, Nicholas "Indy" Ray. All rights reserved.
// See the LICENSE file for usage, modification, and distribution terms.
#include "view_decl.h"
#include "simple_shader.h"
#include "simple_vectors.h"
#include "simple_mesh.h"
#include "simple_texture.h"

#include <gl.h>

struct boot_vert
{
    vector3 location;
    vector2 uv;
};

VertexDef boot_vert_def()
{
    boot_vert* proxy = 0;
    VertexDef VD = CreateVertexDef(sizeof(boot_vert), 2);
    int i = 0;
    AddVertexAttribute(VD, i++, VERTEX_POSITION_ATTR, (size_t)&proxy->location, 3, GL_FLOAT);
    AddVertexAttribute(VD, i++, VERTEX_UV_ATTR, (size_t)&proxy->uv, 2, GL_FLOAT);

    return VD;
}

// Example view implementation.

struct ViewInfo
{
    GLuint basic_shader;
    GLint texture_uniform;
    VertexDef boot_vert;
    GLuint test_mesh;
    GLuint test_texture;
    
    bool bMouseDown;
};

ViewInfo* InitView()
{
    ViewInfo* view = new ViewInfo();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    view->basic_shader = CreateShaderProgram(SHADER_TEXTURED);
    view->texture_uniform = glGetUniformLocation(view->basic_shader,
                                                 "view_texture");

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    view->boot_vert = boot_vert_def();

    boot_vert verts[4];
    verts[0].location.x = -0.90;
    verts[0].location.y = -0.90;
    verts[0].location.z = 0.0;
    verts[0].uv.x = 0.0;
    verts[0].uv.y = 0.0;

    verts[1].location.x = -0.90;
    verts[1].location.y = 0.90;
    verts[1].location.z = 0.0;
    verts[1].uv.x = 0.0;
    verts[1].uv.y = 1.0;

    verts[2].location.x = 0.90;
    verts[2].location.y = -0.90;
    verts[2].location.z = 0.0;
    verts[2].uv.x = 1.0;
    verts[2].uv.y = 0.0;

    verts[3].location.x = 0.90;
    verts[3].location.y = 0.90;
    verts[3].location.z = 0.0;
    verts[3].uv.x = 1.0;
    verts[3].uv.y = 1.0;

    view->test_mesh = CreateMesh(4, sizeof(boot_vert), verts);

    view->bMouseDown = false;

    view->test_texture = CreateTextureFromBMP("test.bmp");

    return view;
}

void FinishView(ViewInfo* view)
{
    DestroyTexture(view->test_texture);
    DestroyMesh(view->test_mesh);
    DestroyVertexDef(view->boot_vert);
    delete view;
}

void ResizeView(ViewInfo*, int, int)
{}

void UpdateView(ViewInfo* view)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(view->basic_shader);
    glBindBuffer(GL_ARRAY_BUFFER, view->test_mesh);
    ApplyVertexDef(view->boot_vert);

    glUniform1i(view->texture_uniform, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, view->test_texture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void MouseDown(ViewInfo* view, int x, int y, MouseButtons butons)
{
    view->bMouseDown = true;
}

void MouseUp(ViewInfo* view, int x, int y, MouseButtons butons)
{
    view->bMouseDown = false;
}

void MouseMove(ViewInfo* view, int x, int y, MouseButtons butons) {}
