#pragma once
#pragma comment(lib, "Opengl32.lib")

#include <Windows.h>
#include <gl/GL.h>
#include <iostream>

#include "structs.h"

struct Color {
	GLubyte r, g, b;
};

namespace gl_draw {
	namespace rgb {
		const Color red = { 255, 55, 55 };
		const Color green = { 0, 255, 0 };
		const Color blue = { 0, 0, 255 };

		const Color yellow = { 255, 255, 0 };

		const Color gray = { 128, 128, 128 };
		const Color lightgray = { 211, 211, 211 };

		const Color black = { 0, 0, 0 };
		const Color white = { 255, 255, 255 };
	}

	constexpr float CONSOLAS_TEXT_WIDTH = 9.f;
	constexpr float CONSOLAS_TEXT_HEIGHT = 15.f;

	// draw in 2d and not 3d
	void Begin2D(const int width = 640, const int height = 640);

	// restore 3d state
	void End2D();


	// ---------------- SHAPES ----------------
	inline Color color = rgb::white; // init white

	// draw a colored outline box
	// x, y: top left
	void DrawBox(float x, float y, float w, float h, /*const GLubyte* color = rgb::white,*/ float lineWidth = 2.0f);
    // Draw a filled box
	// x, y: top left
    void DrawFilledBox(float x, float y, float w, float h/*, const GLubyte* color = rgb::white*/);
    // Draw a line
	void DrawLine(float x1, float y1, float x2, float y2, /*const GLubyte* color = rgb::white,*/ float lineWidth = 1.0f);


	// ---------------- TEXT ----------------
	inline HDC hdc{ nullptr };
	inline GLuint fontBase; // Base index for font display lists
	inline bool fontInitialized{ false };

	void InitFont(); // Initialize bitmap font
	void CleanupFont(); // Optional cleanup (if needed)

	void DisplayText(float x, float y, const Color color, const char* format, ...); // Draw text
	vec3 CenterText(float x, float y, float width, float height, float textWidth = CONSOLAS_TEXT_WIDTH, float textHeight = CONSOLAS_TEXT_HEIGHT);
	float CenterText(float x, float width, float textWidth = CONSOLAS_TEXT_WIDTH);
}