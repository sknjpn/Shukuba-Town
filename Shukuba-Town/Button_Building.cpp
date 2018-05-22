#include "Button_Building.h"
#include "Builder_Building.h"
#include "Field.h"

Button_Building::Button_Building(const RectF& rect, Texture texture)
	: Button(rect, texture)
{

}


Button_Building::~Button_Building()
{
}

void Button_Building::on_clicked()
{
	g_field->set_builder(new Builder_Building());
}
