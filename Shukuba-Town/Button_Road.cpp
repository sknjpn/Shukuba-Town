#include "Button_Road.h"

#include "Field.h"
#include "Builder_Road.h"


Button_Road::Button_Road(const RectF& rect, Texture texture)
	: Button(rect, texture)
{

}


Button_Road::~Button_Road()
{
}

void Button_Road::on_clicked()
{
	g_field->set_builder(new Builder_Road());
}
