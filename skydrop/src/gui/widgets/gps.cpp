#include "gps.h"

void widget_ghdg_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t flags)
{
	uint8_t lh = widget_label_P(PSTR("GHdg"), x, y);

	char tmp[5];
	if (fc.gps_data.valid)
		sprintf_P(tmp, PSTR("%0.0f"), fc.gps_data.heading);
	else
		strcpy_P(tmp, PSTR("---"));


	widget_value_int(tmp, x, y + lh, w, h - lh);
}

void widget_gspd_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t flags)
{
	uint8_t lh = widget_label_P(PSTR("GSpd"), x, y);

	char tmp[5];
	if (fc.gps_data.valid)
	{
		float val;

		switch(config.connectivity.gps_format_flags & GPS_SPD_MASK)
		{
			case(GPS_SPD_KPH):
				val = fc.gps_data.groud_speed * FC_KNOTS_TO_KPH;
			break;

			case(GPS_SPD_MS):
				val = fc.gps_data.groud_speed * FC_KNOTS_TO_MPS;
			break;

			case(GPS_SPD_MPH):
				val = fc.gps_data.groud_speed * FC_KNOTS_TO_MPH;
			break;

			case(GPS_SPD_KNOT):
				val = fc.gps_data.groud_speed;
			break;
		}

		sprintf_P(tmp, PSTR("%0.0f"), val);
	}
	else
		strcpy_P(tmp, PSTR("---"));


	widget_value_int(tmp, x, y + lh, w, h - lh);
}

void widget_gpos_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t flags)
{
	uint8_t lh = widget_label_P(PSTR("GPos"), x, y);

	if (fc.gps_data.valid)
	{
		widget_value_txt2((char *)fc.gps_data.cache_gui_latitude,
				(char *)fc.gps_data.cache_gui_longtitude, x, y + lh, w, h - lh);
	}
	else
	{
		char tmp[4];
		strcpy_P(tmp, PSTR("---"));
		widget_value_int(tmp, x, y + lh, w, h - lh);
	}


}

void widget_ghdg_arrow_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t flags)
{
	uint8_t lh = widget_label_P(PSTR("GHdg"), x, y);

	y += lh / 2;

	if (fc.gps_data.valid)
	{
		widget_arrow(fc.gps_data.heading, x, y, w, h);
	}
	else
	{
		char tmp[5];
		strcpy_P(tmp, PSTR("---"));
		widget_value_int(tmp, x, y + lh, w, h - lh);
	}

}

void widget_gcompass_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t flags)
{
	uint8_t lh = widget_label_P(PSTR("GCom"), x, y);

	y += lh / 2;

	if (fc.gps_data.valid)
	{
		int16_t compass = 360 - fc.gps_data.heading;

		widget_arrow(compass, x, y, w, h);
	}
	else
	{
		char tmp[5];
		strcpy_P(tmp, PSTR("---"));
		widget_value_int(tmp, x, y + lh, w, h - lh);
	}

}

void widget_ghdg_dir_draw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t flags)
{
	uint8_t lh = widget_label_P(PSTR("GHdg"), x, y);

	char tmp[5];
	if (fc.gps_data.valid)
	{
		float dir = fc.gps_data.heading;
		if (22.5 <= dir and dir <  67.5)
			strcpy_P(tmp, PSTR("NE"));
		else if( 67.5 <= dir and dir < 112.5)
			strcpy_P(tmp, PSTR("E"));
		else if(112.5 <= dir and dir < 157.5)
			strcpy_P(tmp, PSTR("SE"));
		else if(157.5 <= dir and dir < 202.5)
			strcpy_P(tmp, PSTR("S"));
		else if(202.5 <= dir and dir < 247.5)
			strcpy_P(tmp, PSTR("SW"));
		else if(247.5 <= dir and dir < 292.5)
			strcpy_P(tmp, PSTR("W"));
		else if(292.5 <= dir and dir < 337.5)
			strcpy_P(tmp, PSTR("NW"));
		else
			strcpy_P(tmp, PSTR("N"));
	}
	else
		strcpy_P(tmp, PSTR("---"));


	widget_value_txt(tmp, x, y + lh, w, h - lh);
}

register_widget1(w_gps_hdg, "GPS heading", widget_ghdg_draw);
register_widget1(w_gps_hdg_arrow, "GPS HDG arrow", widget_ghdg_arrow_draw);
register_widget1(w_gps_hdg_points, "GPS HDG points", widget_ghdg_dir_draw);

register_widget1(w_gps_speed, "Ground speed", widget_gspd_draw);
register_widget1(w_gps_position, "GPS position", widget_gpos_draw);

