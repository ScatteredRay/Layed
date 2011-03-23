// Copyright (c) 2010, Nicholas "Indy" Ray. All rights reserved.
// See the LICENSE file for usage, modification, and distribution terms.
#ifndef _VIEW_DECL_H_
#define _VIEW_DECL_H_

// This is a simple set of declerations used to render views, this is the
// interface between the system libraries back into the view.

struct ViewInfo;

ViewInfo* InitView();
// Standard destruction function named because it's up to view to determine
// if it actually destroys anything.
void FinishView(ViewInfo*);
void ResizeView(ViewInfo*, int width, int height);
void UpdateView(ViewInfo*);

enum MouseButtons
{
    No_Button = 0,
    Left_Button = 1 << 0,
    Right_Button = 1 << 1,
    Mid_Button = 1 << 2
};

void MouseDown(ViewInfo* view, int x, int y, MouseButtons butons);
void MouseUp(ViewInfo* view, int x, int y, MouseButtons butons);
void MouseMove(ViewInfo* view, int x, int y, MouseButtons butons);

#endif //_VIEW_DECL_H_
