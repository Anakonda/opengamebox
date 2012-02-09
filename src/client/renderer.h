#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "../irenderer.h"
#include "../vector2.h"
#include "../color.h"

class Renderer : public IRenderer{
public:
	Renderer(Vector2 screenSize);
	~Renderer();

	virtual void updateTransformations();

	virtual void mulScreenZoom(float zoom);
	virtual void addScreenLocation(Vector2 location);
	virtual void setScreenSize(Vector2 screenSize);

	virtual void drawBitmap(std::string texture, Vector2 source_location,
	                        Vector2 source_size, Vector2 dest_location,
	                        Vector2 dest_size);
	virtual void drawBitmapTinted(std::string texture, Vector2 source_location,
                            Vector2 source_size, Vector2 dest_location,
                            Vector2 dest_size, Color color);
	virtual void drawRectangle(Vector2 pointA, Vector2 pointB, Color color, float thickness);

	virtual Coordinates getTextureSize(std::string texture);

	virtual void transformLocation(Transformation transformation, Vector2 &location);
	virtual void useTransform(Transformation transformation);

	virtual void hsvToRgb(float hue, float saturation, float value, Color *color);

private:
	ALLEGRO_TRANSFORM camera;
	ALLEGRO_TRANSFORM camera_inverse;
	ALLEGRO_TRANSFORM cameraUI;

	Vector2 screenSize;
	float screenZoom;
	Vector2 screenLocation;
	float screenRotation;

	std::map<std::string, ALLEGRO_BITMAP*> textures;

	void loadTexture(std::string);

	ALLEGRO_TRANSFORM* getTransformation(Transformation transformation);
};

#endif
