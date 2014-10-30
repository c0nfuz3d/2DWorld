/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

#include "dropdown_menu.h"
#include "cursor.h"
#include <iostream>

void dropdown_menu::add_item(button* b)
{
    b->border=false;
    b->allign_label("left");
	items.push_back(b);
    format();//match menu width to the width of the widest item
    //make all the items the same size
    for(auto i:items)
        i->set_dimensions(width,items.back()->get_height());
    set_dimensions(width,items.front()->get_height());//match menu height to item height
}

void dropdown_menu::mouse_function()
{
    if(hovered_over() && !primary_color.changed)
        primary_color.brighten();
    if(!hovered_over())
        primary_color.undo();
    if(left_clicked()||item_clicked())
    {
        if(expanded)
        {
            if(state_toggle)
            expand();
            state_toggle=false;
        }
        else
        {
            if(!state_toggle)
                collapse();
            state_toggle=true;
        }
    }
    else
        expanded=state_toggle;
}

void dropdown_menu::expand()
{
    for(auto i:items)
        i->show();//show the buttons
}

void dropdown_menu::collapse()
{
    set_dimensions(width,items.front()->get_height());//shrink to button size
}

void dropdown_menu::update()
{
    for(auto i:items)
    {
		if(state_toggle && visible)
        	i->show();
		else
			i->hide();
        i->update();
    }
    mouse_function();
}

dropdown_menu::dropdown_menu()
{
	type="dropdown menu";
	set_title("choose one");
	allign_title("middle");
	title.set_font("helvetica",12);
    subtitle.hide();
    layout = "vertical";
    spacing=0;
    margin=0;
    expanded=false;
	std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}