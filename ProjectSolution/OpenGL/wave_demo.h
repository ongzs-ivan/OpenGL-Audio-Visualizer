#ifndef _WAVE_DEMO_H
#define _WAVE_DEMO_H

#include "demo_base.h"
#include "bitmap.h"
#include <vector>

#define TEXTURE_COUNT 1

#define RECT_VERTICE_W 50
#define RECT_VERTICE_H 50

//every quad has 6 vertices
const int RECT_VERTEX_COUNT = (RECT_VERTICE_W-1)*(RECT_VERTICE_H-1)*6;

//every vertex has 3 components(x, y z)
const int RECT_VERTEX_ARRAY_SIZE = RECT_VERTEX_COUNT*3;


// U, V arrays
const int RECT_UV_ARRAY_SIZE = RECT_VERTEX_COUNT*2;

class WaveDemo : public DemoBase
{

private:
	GLuint mTextureID[TEXTURE_COUNT];
	
	float mWaveRadianOffset;
	GLfloat mRectVertices[RECT_VERTEX_ARRAY_SIZE];
	GLfloat mRectUV[RECT_UV_ARRAY_SIZE];

	void loadTexture(const char* path, GLuint textureID)
	{
		CBitmap bitmap(path);

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // apply texture wrapping along horizontal part.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // apply texture wrapping along vertical part.

		// bilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering. (For when texture needs to scale up on screen)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering. (For when texture need to scale down on screen)
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
	}

public:
	void init()
	{
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("./media/water2.bmp", mTextureID[0]);
		
		mWaveRadianOffset = 0.0f;
	}

	void deinit()
	{

	}

	void genPlane(float offsetRadian)
	{
		const float width = 5.0f;
		const float height = 5.0f;
		const float halfWidth = width * 0.5f;
		const float halfHeight = height * 0.5f;

		const float waveAmpMul = 0.1f;
		const float xToRadianMul = 5.0f;

		const float texMul = 10.0f;

		int currentVert = -1;
		int currentIndex = -1;
		for(int h=0; h<RECT_VERTICE_H-1; h++)
		{
			for(int w=0; w<RECT_VERTICE_W-1; w++)
			{
				//========= 6 vertices to form one sub-rectangle

				//1st vertex
				int vertex1 = ++currentVert;
				mRectVertices[vertex1*3] = -halfWidth + (float)(w)/(float)RECT_VERTICE_W * width;
				mRectVertices[vertex1*3+1] = waveAmpMul * cos(offsetRadian+ mRectVertices[vertex1*3]*xToRadianMul);
				mRectVertices[vertex1*3+2] = -halfHeight + (float)(h)/(float)RECT_VERTICE_H * height;
				mRectUV[vertex1*2] = (float)(w)/(float)RECT_VERTICE_W * texMul;
				mRectUV[vertex1*2+1] = (float)(h)/(float)RECT_VERTICE_H* texMul;

				//2nd vertex
				int vertex2 = ++currentVert;
				mRectVertices[vertex2*3] = -halfWidth + (float)(w)/(float)RECT_VERTICE_W * width;
				mRectVertices[vertex2*3+1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex2*3]*xToRadianMul);
				mRectVertices[vertex2*3+2] = -halfHeight + (float)(h+1)/(float)RECT_VERTICE_H * height;
				mRectUV[vertex2*2] = (float)(w)/(float)RECT_VERTICE_W* texMul;
				mRectUV[vertex2*2+1] = (float)(h+1)/(float)RECT_VERTICE_H* texMul;


				//3rd vertex
				int vertex3 = ++currentVert;
				mRectVertices[vertex3*3] = -halfWidth + (float)(w+1)/(float)RECT_VERTICE_W * width;
				mRectVertices[vertex3*3+1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex3*3]*xToRadianMul);
				mRectVertices[vertex3*3+2] = -halfHeight + (float)(h+1)/(float)RECT_VERTICE_H * height;
				mRectUV[vertex3*2] = (float)(w+1)/(float)RECT_VERTICE_W * texMul;
				mRectUV[vertex3*2+1] = (float)(h+1)/(float)RECT_VERTICE_H * texMul;


				//4th vertex
				int vertex4 = ++currentVert;
				mRectVertices[vertex4*3] = mRectVertices[vertex3*3];
				mRectVertices[vertex4*3+1] = mRectVertices[vertex3*3+1];
				mRectVertices[vertex4*3+2] = mRectVertices[vertex3*3+2];
				mRectUV[vertex4*2] = mRectUV[vertex3*2];
				mRectUV[vertex4*2+1] = mRectUV[vertex3*2+1];


				//5th vertex
				int vertex5 = ++currentVert;
				mRectVertices[vertex5*3] = -halfWidth + (float)(w+1)/(float)RECT_VERTICE_W * width;
				mRectVertices[vertex5*3+1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex5*3]*xToRadianMul);
				mRectVertices[vertex5*3+2] = -halfHeight + (float)(h)/(float)RECT_VERTICE_H * height;
				mRectUV[vertex5*2] = (float)(w+1)/(float)RECT_VERTICE_W * texMul;
				mRectUV[vertex5*2+1] = (float)(h)/(float)RECT_VERTICE_H * texMul;

				//6th vertex
				int vertex6 = ++currentVert;
				mRectVertices[vertex6*3] = mRectVertices[vertex1*3];
				mRectVertices[vertex6*3+1] = mRectVertices[vertex1*3+1];
				mRectVertices[vertex6*3+2] = mRectVertices[vertex1*3+2];
				mRectUV[vertex6*2] = mRectUV[vertex1*2];
				mRectUV[vertex6*2+1] = mRectUV[vertex1*2+1];
			}
		}
	}
	void drawWorldOriginLines(const Matrix& viewMatrix)
	{
		// draw axis.
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.3f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			glColor3f(0.3f, 1.0f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			glColor3f(0.3f, 0.3f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
	}

	void drawWave()
	{


		mWaveRadianOffset += 0.01f;
		if(mWaveRadianOffset > 2.0f * M_PI)
			mWaveRadianOffset -= 2.0f * M_PI;
		genPlane(mWaveRadianOffset);

		glColor3f(1.0f, 1.0f, 1.0f);
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0,  mRectVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, mRectUV);

		glDrawArrays(GL_TRIANGLES, 0, RECT_VERTEX_COUNT);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void draw(const Matrix& viewMatrix)
	{
		// draw axis.
		drawWorldOriginLines(viewMatrix);

		Matrix rotate1 = Matrix::makeRotateMatrix(0, Vector(0.0f, 0.0f, 1.0f));
		Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, 0.0f, 0.0f);

		// NOTE on OpenGL Matrix model:
		// Screen = Proj * View * Model
		// Model = TransformA(3rd) * TransformB(2nd) * TransformC(1st) (Trasnform could be Rotate, Scale, Translate, etc)
		
		// perform model transformation
		Matrix modelMatrix = translate1 * rotate1;

		// convert model space to view space
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);		

		drawWave();
	}

	void SongChanger(int input)
	{

	}
};

#endif
