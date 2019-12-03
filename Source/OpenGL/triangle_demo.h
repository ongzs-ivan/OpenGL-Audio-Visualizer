#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"
#include "bitmap.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <stdio.h>

#define TEXTURE_COUNT 1

// must be 2 to the power of any number
#define SPECTRUM_SIZE 256

const int arraySize = 10;

#define _USE_MATH_DEFINES
#include <math.h>

//fmod error checking function
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

class TriangleDemo : public DemoBase
{
private:
	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel* m_musicChannel;

	float m_spectrumLeft[SPECTRUM_SIZE];
	float m_spectrumRight[SPECTRUM_SIZE];
	float m_spectrumAvg[SPECTRUM_SIZE];

	float m_spin;
	float m_spin2;

	GLfloat mRectVertices[18];

	GLuint mTextureID[TEXTURE_COUNT];

	void loadTexture(const char* path, GLuint textureID)
	{
		CBitmap bitmap(path);

		// Create linear filtered texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //apply texture wrapping along horizontal
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //apply texture wrapping along vertical

		// old school (minecraft) filtering
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // near filtering
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // far filtering
		//

		//bilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(),
			0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
	}

public:
	void initFmod()
	{
		FMOD_RESULT result;
		unsigned int version;

		result = FMOD::System_Create(&m_fmodSystem);
		ERRCHECK(result);

		result = m_fmodSystem->getVersion(&version);
		ERRCHECK(result);

		if (version < FMOD_VERSION)
			printf("FMOD Error! You are using an old version of FMOD.", version, FMOD_VERSION);

		// initialize fmod system
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ERRCHECK(result);

		// load and set up music
		result = m_fmodSystem->createStream("../media/wow.mp3", FMOD_SOFTWARE, 0, &m_music);
		//result = m_fmodSystem->createStream("../media/20Hz-20kHZ.mp3", FMOD_SOFTWARE, 0, &m_music);

		MusicMenu();
		Signature();

		// play the loaded mp3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);

		// set sound channel loop count
		m_musicChannel->setLoopCount(0);
	}

	void init()
	{
		initFmod();
		m_spin = 0.0f;
		m_spin2 = 0.0f;
	}

	void deinit()
	{

	}

	void drawAxis(const Matrix& viewMatrix)
	{
		// ============draw axis.
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
		// ============================
	}

	void MusicMenu()
	{
		std::system("CLS");
		std::cout << "Privyet Eevan's Audio Visualizer v1.0" << std::endl << std::endl;
		std::cout << "[SONG MENU]" << std::endl;
		std::cout << "1. Asian Kungfu Generation - Blood Circulator" << std::endl;
		std::cout << "2. Daisuke Ishiwatari - Big Blast Sonic" << std::endl;
		std::cout << "3. Daisuke Ishiwatari - Safe Intoxication" << std::endl;
		std::cout << "4. Daisuke Ishiwatari - Wanna Be Crazy" << std::endl;
		std::cout << "5. Daisuke Ishiwatari - Heavy Day" << std::endl;
		std::cout << "6. Jin - Lost Time Memory (ft. Matsuyama Kouta)" << std::endl;
		std::cout << "7. Jin - Lost Time Memory (ft. IA)" << std::endl << std::endl;
	}

	void Signature()
	{
		std::cout << std::endl << "\"It's free audio estate \" - Ivan, 2019" << std::endl;
		std::cout << std::endl << "[by 0124846 - Ivan Ong Zhisien]" << std::endl;
	}

	void SongChanger(int input)
	{
		FMOD_RESULT		result;
		result = m_musicChannel->stop();
		if (input == 1)
		{
			//Load and setup music
			result = m_fmodSystem->createStream("../media/Blood Circulator.mp3", FMOD_SOFTWARE, 0, &m_music);
			ERRCHECK(result);

			//Play the loaded MP3 music
			result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
			ERRCHECK(result);

			MusicMenu();
			std::cout << "[Now Playing] --- Asian Kungfu Generation - Blood Circulator ---" << std::endl;
			Signature();
		}

		else if (input == 2)
		{
			//Load and setup music
			result = m_fmodSystem->createStream("../media/Big Blast Sonic.mp3", FMOD_SOFTWARE, 0, &m_music);
			ERRCHECK(result);

			//Play the loaded MP3 music
			result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
			ERRCHECK(result);

			MusicMenu();
			std::cout << "[Now Playing] --- Daisuke Ishiwatari - Big Blast Sonic ---" << std::endl;
			Signature();
		}
		else if (input == 3)
		{
			//Load and setup music
			result = m_fmodSystem->createStream("../media/Safe Intoxication.mp3", FMOD_SOFTWARE, 0, &m_music);
			ERRCHECK(result);

			//Play the loaded MP3 music
			result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
			ERRCHECK(result);

			MusicMenu();
			std::cout << "[Now Playing] --- Daisuke Ishiwatari - Safe Intoxication ---" << std::endl;
			Signature();
		}
		else if (input == 4)
		{
			//Load and setup music
			result = m_fmodSystem->createStream("../media/Wanna Be Crazy.mp3", FMOD_SOFTWARE, 0, &m_music);
			ERRCHECK(result);

			//Play the loaded MP3 music
			result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
			ERRCHECK(result);

			MusicMenu();
			std::cout << "[Now Playing] --- Daisuke Ishiwatari - Wanna Be Crazy ---" << std::endl;
			Signature();
		}
		else if (input == 5)
		{
			//Load and setup music
			result = m_fmodSystem->createStream("../media/Heavy Day.mp3", FMOD_SOFTWARE, 0, &m_music);
			ERRCHECK(result);

			//Play the loaded MP3 music
			result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
			ERRCHECK(result);

			MusicMenu();
			std::cout << "[Now Playing] --- Daisuke Ishiwatari - Heavy Day ---" << std::endl;
			Signature();
		}
		else if (input == 6)
		{
		//Load and setup music
		result = m_fmodSystem->createStream("../media/Lost Time Memory.mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		//Play the loaded MP3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);

		MusicMenu();
		std::cout << "[Now Playing] --- Jin - Lost Time Memory ---" << std::endl;
		Signature();
		}
		else if (input == 7)
		{
		//Load and setup music
		result = m_fmodSystem->createStream("../media/Lost Time Memory (IA).mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		//Play the loaded MP3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);

		MusicMenu();
		std::cout << "[Now Playing] --- Jin - Lost Time Memory (IA vocals) ---" << std::endl;
		Signature();
		}
	}

	void draw2DBar(float height)
	{
		const float hWidth = 0.2f;

		GLfloat vertices[] =
		{
			-hWidth, 0.0f, 0.0f,
			hWidth, 0.0f, 0.0f,
			hWidth, height, 0.0f,

			hWidth, height, 0.0f,
			-hWidth, height, 0.0f,
			-hWidth, 0.0f, 0.0f,
		};

		GLubyte colors[] =
		{
			255, 0, 0, 255,
			255, 0, 0, 255,
			255, 255, 0, 255,

			255, 255, 0, 255,
			255, 255, 0, 255,
			255, 0, 0, 255,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

		// draw rectangle
		glDrawArrays(GL_TRIANGLES, 0, 6); // 6 is the number of total vertices

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void AudioBar(const Matrix& viewMatrix)
	{
		int barCount = 32;
		float barGap = 0.5f;
		float startX = -(float)barCount * 0.5f * barGap;
		Matrix translate1;
		Matrix viewSpaceMatrix;

		for (int i = 0; i < barCount; i++)
		{
			translate1 = Matrix::makeTranslationMatrix(startX + 0.25f + 0.5f * i, 0.0f, 0.0f);
			viewSpaceMatrix = viewMatrix * translate1;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

			float height = m_spectrumAvg[i];
			draw2DBar(height * 2.0f); //multiplies with 2.0 to make the bar taller
		}
	}

	void draw3DRingSection(float radius, float height1, float height2, float thickness, float angle, int section)
	{
		//inner circle
		float radius2 = radius - thickness;

		//One section has 24 vertices for Outer, Inner, Upper, Lower faces of the ring

		GLfloat vertices[] =
		{
			// outer
			radius * cos(angle * section), (height1 / 2), radius * sin(angle * section),
			radius * cos(angle * section), (-height1 / 2), radius * sin(angle * section),
			radius * cos(angle * (section + 1)), (-height2 / 2), radius * sin(angle * (section + 1)),
			radius * cos(angle * (section + 1)), (-height2 / 2), radius * sin(angle * (section + 1)),
			radius * cos(angle * (section + 1)), (height2 / 2), radius * sin(angle * (section + 1)),
			radius * cos(angle * section), (height1 / 2), radius * sin(angle * section),

			// inner
			radius2 * cos(angle * section), (height1 / 2), radius2 * sin(angle * section),
			radius2 * cos(angle * section), (-height1 / 2), radius2 * sin(angle * section),
			radius2 * cos(angle * (section + 1)), (-height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * (section + 1)), (-height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * (section + 1)), (height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * section), (height1 / 2), radius2 * sin(angle * section),

			//top
			radius * cos(angle * section), (height1 / 2), radius * sin(angle * section),
			radius * cos(angle * (section + 1)), (height2 / 2), radius * sin(angle * (section + 1)),
			radius2 * cos(angle * (section + 1)), (height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * (section + 1)), (height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * section), (height1 / 2), radius2 * sin(angle * section),
			radius * cos(angle * section), (height1 / 2), radius * sin(angle * section),

			//bottom
			radius * cos(angle * section), (-height1 / 2), radius * sin(angle * section),
			radius * cos(angle * (section + 1)), (-height2 / 2), radius * sin(angle * (section + 1)),
			radius2 * cos(angle * (section + 1)), (-height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * (section + 1)), (-height2 / 2), radius2 * sin(angle * (section + 1)),
			radius2 * cos(angle * section), (-height1 / 2), radius2 * sin(angle * section),
			radius * cos(angle * section), (-height1 / 2), radius * sin(angle * section),
		};

		GLubyte colors[] =
		{
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
			255, 255, 0, 200,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

		// draw rectangle
		glDrawArrays(GL_TRIANGLES, 0, 24); // 6 is the number of total vertices

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void draw3DRing(const Matrix& viewMatrix, float rotateAngle, float magnitude)
	{
		int sections = 128;
		float angle = 2 * M_PI / sections;
		float height1 = 0.0f;
		float height2 = 0.0f;

		Matrix rotate = Matrix::makeRotateMatrix(rotateAngle, Vector(0.0f, 1.0f, 0.0f));
		Matrix modelMatrix = viewMatrix * rotate;

		glLoadMatrixf((GLfloat*)modelMatrix.mVal);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (int i = 0; i < sections; i++)
		{

			if (i == 0)
			{
				height1 = magnitude * m_spectrumAvg[sections];
			}
			else
			{
				height1 = magnitude * m_spectrumAvg[i];
			}

			if (i < sections)
			{
				height2 = magnitude * m_spectrumAvg[i+1];
			}
			else if (i == sections)
			{
				height2 = magnitude * m_spectrumAvg[0];
			}
			draw3DRingSection(5, height1, height2, 0.05, angle, i);
		}
		glDisable(GL_BLEND);
	}

	void drawSphereSegment(float radius, float latAngle, float longAngle, float latSegment, float longSeg, int r, int g, int b, int alphaGradient)
	{
		GLfloat vertices[] =
		{
			radius * sin(latAngle * latSegment) * cos(longAngle * ( longSeg)),
			radius * sin(latAngle * latSegment) * sin(longAngle * ( longSeg)),
			radius * cos(latAngle * latSegment),
				   
			radius * sin(latAngle * (latSegment + 1)) * cos(longAngle * ( longSeg)),
			radius * sin(latAngle * (latSegment + 1)) * sin(longAngle * ( longSeg)),
			radius * cos(latAngle * (latSegment + 1)),
				   
			radius * sin(latAngle * (latSegment + 1)) * cos(longAngle * ( longSeg + 1)),
			radius * sin(latAngle * (latSegment + 1)) * sin(longAngle * ( longSeg + 1)),
			radius * cos(latAngle * (latSegment + 1)),
				   
			radius * sin(latAngle * (latSegment + 1)) * cos(longAngle * ( longSeg + 1)),
			radius * sin(latAngle * (latSegment + 1)) * sin(longAngle * ( longSeg + 1)),
			radius * cos(latAngle * (latSegment + 1)),

			radius * sin(latAngle * latSegment) * cos(longAngle * ( longSeg + 1)),
			radius * sin(latAngle * latSegment) * sin(longAngle * ( longSeg + 1)),
			radius * cos(latAngle * latSegment),

			radius * sin(latAngle * latSegment) * cos(longAngle * ( longSeg)),
			radius * sin(latAngle * latSegment) * sin(longAngle * ( longSeg)),
			radius * cos(latAngle * latSegment),
		};

		GLubyte colors[] =
		{
			r, g, b, alphaGradient,
			r, g, b, alphaGradient,
			r, g, b, alphaGradient,
			r, g, b, alphaGradient,
			r, g, b, alphaGradient,
			r, g, b, alphaGradient,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

		// draw rectangle
		glDrawArrays(GL_TRIANGLES, 0, 6); // 6 is the number of total vertices

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawCentreSphere(const Matrix& viewMatrix, float radius, float latSeg, float longSeg)
	{
		float latAngle = M_PI / latSeg;
		float longAngle = 2 * M_PI / longSeg;
		float newRadius = radius;
		float tempNo;

		Matrix rotate = Matrix::makeRotateMatrix(90, Vector(1.0f, 0.0f, 0.0f));
		Matrix spin = Matrix::makeRotateMatrix(m_spin * 10, Vector(0.0f, 0.0f, 1.0f));
		Matrix translate = Matrix::makeTranslationMatrix(Vector(0.0f, 0.0f, 0.0f));
		Matrix modelMatrix = viewMatrix * rotate * translate * spin;

		glLoadMatrixf((GLfloat*)modelMatrix.mVal);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(false);
		for (int i = 0; i < longSeg; i++)
		{
			for (int j = 0; j < latSeg; j++)
			{
				tempNo = m_spectrumAvg[rand()%SPECTRUM_SIZE];
				if (tempNo > 0.1)
				{
					newRadius = radius * m_spectrumAvg[j];;
				}

				if (newRadius < radius)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
					newRadius = radius;
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				drawSphereSegment(newRadius, latAngle, longAngle, j, i, 255, 0, 0, m_spectrumAvg[j] * 255 * 2);
			}
		}
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void drawSkyBoxSphere(const Matrix& viewMatrix, float angle, float radius, float latSeg, float longSeg)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

		float latAngle = M_PI / latSeg;
		float longAngle = 2 * M_PI / longSeg;
		float tempBrightness;

		Matrix rotate = Matrix::makeRotateMatrix(angle, Vector(1.0f, 0.0f, 0.0f));
		Matrix translate = Matrix::makeTranslationMatrix(Vector(0.0f, 0.0f, 0.0f));
		Matrix modelMatrix = viewMatrix * rotate * translate;
		glLoadMatrixf((GLfloat*)modelMatrix.mVal);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(false);
		for (int i = 0; i < longSeg; i++)
		{
			for (int j = 0; j < latSeg; j++)
			{
				tempBrightness = m_spectrumAvg[j] * 255;
				if (m_spectrumAvg[j] > 0.3)
				{
					tempBrightness = 30;
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				}
				drawSphereSegment(radius, latAngle, longAngle, j, i, 255, 255, 255, tempBrightness);
			}
		}
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void drawRotatingSegment(const Matrix& viewMatrix, float angle, float radius, float latSeg, float longSeg)
	{
		float latAngle = M_PI / latSeg;
		float longAngle = 2 * M_PI / longSeg;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		Matrix rotate = Matrix::makeRotateMatrix(90, Vector(1.0f, 0.0f, 0.0f));
		Matrix rotate2 = Matrix::makeRotateMatrix(angle, Vector(0.0f, 0.0f, 1.0f));
		Matrix spin = Matrix::makeRotateMatrix(m_spin2, Vector(0.0f, 1.0f, 0.0f));
		Matrix modelMatrix = viewMatrix * spin * rotate * rotate2;
		glLoadMatrixf((GLfloat*)modelMatrix.mVal);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(false);

		for (int i = 0; i < longSeg; i++)
		{
			drawSphereSegment(radius, latAngle, longAngle, i, 1, 55, 55, 255, m_spectrumAvg[i] * 155 * 2);
		}
		
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void drawPyramid(float size, float height)
	{
		GLfloat vertices[] =
		{
			-size, 0.0f, size,
			size, 0.0f, size,
			0.0f, height, 0.0f,

			size, 0.0f, size,
			size, 0.0f, -size,
			0.0f, height, 0.0f,

			size, 0.0f, -size,
			-size, 0.0f, -size,
			0.0f, height, 0.0f,

			-size, 0.0f, -size,
			-size, 0.0f, size,
			0.0f, height, 0.0f,
		};

		GLubyte colors[] =
		{
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
			0, 150, 0, 30,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

		// draw rectangle
		glDrawArrays(GL_TRIANGLES, 0, 12); // 6 is the number of total vertices

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawDiamond(const Matrix& viewMatrix, float size, float height)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Matrix rotate = Matrix::makeRotateMatrix(90, Vector(0.0f, 1.0f, 0.0f));
		Matrix modelMatrix = viewMatrix  * rotate;
		glLoadMatrixf((GLfloat*)modelMatrix.mVal);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(false);

		float newSize = size * m_spectrumAvg[0] * 1;
		if (newSize < size)
		{
			drawPyramid(newSize, height);
			drawPyramid(newSize, -height);
		}
		else
		{
			drawPyramid(size, height);
			drawPyramid(size, -height);
		}

		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void updateFmod()
	{
		m_fmodSystem->update();

		// Get spectrum for left and right stereo channels
		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		//std::cout << m_spectrumLeft[SPECTRUM_SIZE] << "," << m_spectrumRight[SPECTRUM_SIZE] << std::endl;

		// average the first left and right spectrum
		for (int i = 0; i < SPECTRUM_SIZE; i++)
		{
			m_spectrumAvg[i] = (m_spectrumLeft[i] + m_spectrumRight[i]/2);
		}
	}

	void draw(const Matrix& viewMatrix)
	{
		updateFmod();
		m_spin += 0.05f;
		m_spin2 += (m_spectrumAvg[1] * 2) * 20;
		//drawAxis(viewMatrix);

		//AudioBar(viewMatrix);
		draw3DRing(viewMatrix, 0.0f, 5.0f);
		draw3DRing(viewMatrix, 180.0f, 5.0f);
		drawCentreSphere(viewMatrix, 2, 40, 40);
		drawSkyBoxSphere(viewMatrix, 90, 20, 40, 40);
		drawSkyBoxSphere(viewMatrix, -90, 20, 40, 40);
		drawRotatingSegment(viewMatrix, 0, 20, 20, 20);
		drawRotatingSegment(viewMatrix, 180, 20, 20, 20);
		drawDiamond(viewMatrix, 7, 20);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//enable wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}

};

#endif