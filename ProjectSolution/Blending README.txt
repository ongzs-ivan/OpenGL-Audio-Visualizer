-------------------
| To use Blending |
-------------------

[STEP 1: Enable blend before drawing an object]

glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA); // Alpha blend
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Add blend
		//glBlendFunc(GL_DST_COLOR, GL_ZERO); // Multiply blend

[STEP 2: Disable blend after drawing]

glDisable(GL_BLEND);

---------------------
|  To add "Realism" |
---------------------

[STEP 1: Add the following line in either the draw function or whenever drawing shapes]

glDepthMask(false);

NOTES:
- Can only be used with Add blend
- Is used to make openGL render textures behind another texture

> As a test, first disable the blend, then draw a big cube with no textures. 
Then re-enable the blend and draw a smaller cube in front with textures