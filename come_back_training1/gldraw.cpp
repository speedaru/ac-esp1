#include "gldraw.h"

void gl_draw::Begin2D(const int width, const int height) {
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint viewport[4]; // x, y, w, h of window
	glGetIntegerv(GL_VIEWPORT, viewport);
	//glViewport(0, 0, viewport[2], viewport[3]); // set vp 0, 0 -> top left | index 2 & 3 are w & h
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	//glDisable(GL_DEPTH_TEST);
}

void gl_draw::End2D() {
	//glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void gl_draw::DrawBox(float x, float y, float w, float h, /*const GLubyte* color,*/ float lineWidth) {
	glLineWidth(lineWidth);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	// 
	//glVertex2f(x - w, y - h);
	//glVertex2f(x + w, y - h);
	//glVertex2f(x + w, y + h);
	//glVertex2f(x - w, y + h);
	glEnd();
}

void gl_draw::DrawFilledBox(float x, float y, float w, float h/*, const GLubyte* color*/ ) {
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_QUADS);
	glVertex2f(x - w, y - h);
	glVertex2f(x + w, y - h);
	glVertex2f(x + w, y + h);
	glVertex2f(x - w, y + h);
	glEnd();
}

void gl_draw::DrawLine(float x1, float y1, float x2, float y2, /*const GLubyte* color,*/ float lineWidth) {
	glLineWidth(lineWidth);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}


// ---------------- TEXT ----------------
void gl_draw::InitFont() {
	hdc = wglGetCurrentDC();
	HFONT hFont = CreateFontA(-15, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	fontBase = glGenLists(128);
	wglUseFontBitmapsA(hdc, 0, 128, fontBase);
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

	fontInitialized = true;
}
void gl_draw::CleanupFont() {
	if (fontInitialized && fontBase) {
		glDeleteLists(fontBase, 128);
		fontBase = 0;
		fontInitialized = false;
		printf("Font cleaned up\n");
	}
}

void gl_draw::DisplayText(float x, float y, const Color color, const char* format, ...) {
	if (!fontBase) {
		printf("DisplayText failed: fontBase is 0\n");
		return;
	}

	glColor3ub(color.r, color.g, color.b);
	glRasterPos2f(x, y);

	va_list args;
	va_start(args, format);

	char text[256];
	vsnprintf_s(text, sizeof(text), format, args);

	va_end(args);

	glPushAttrib(GL_LIST_BIT);
	glListBase(fontBase);
	glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}
vec3 gl_draw::CenterText(float x, float y, float width, float height, float textWidth, float textHeight) {
	vec3 text;
	text.x = x + ((width - textWidth) / 2);
	text.y = y + textHeight;
	return text;
}
float gl_draw::CenterText(float x, float width, float textWidth) {
	return x + ((width - textWidth) / 2);
}