/***************************************************************************
 *   Copyright (C) 2008 by Damien RANNOU,,,   *
 *   damunix@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "libgpsconnector.h"

LibGpsConnector::LibGpsConnector()
 : Gps()
{
}


LibGpsConnector::~LibGpsConnector()
{
}


bool LibGpsConnector::start()
{
	qDebug("starting gps");
	m_gpsdata = gps_open("127.0.0.1", "2947");
	if (m_gpsdata == NULL)
	{
		qFatal("Could not open gps device");
	}
	gps_query(m_gpsdata, "w+x\n");
	return true;
}

bool LibGpsConnector::stop() 
{
	return false;
}

int LibGpsConnector::updateGpsData()
{
	/*if(m_gpsdata->online)
	{
		if(gps_query(m_gpsdata, "o\n"))
		{
			return query_error;
		}

		if(m_gpsdata->status > 0)
		{
			memcpy(&data, &(m_gpsdata->fix), sizeof(struct gps_fix_t));
			return ok;
		}

		return -2;
	}
*/
	return -1;
}
bool LibGpsConnector::isOnline()
{
	if (m_gpsdata->online != 0)
		return true;
	return false;
}

bool LibGpsConnector::isFix()
{
	if (m_gpsdata->status == 0)
		return false;
// 	else
	return true;
}
int LibGpsConnector::satellitesUsed()
{
	return m_gpsdata->satellites_used;
}

double LibGpsConnector::getLatitude() 
{
	if (m_gpsdata->fix.mode <2)
		qFatal("mode < 2, can't get latitude");
	return m_gpsdata->fix.latitude;
}

double LibGpsConnector::getLongitude() 
{
	return 0.0;
}

double LibGpsConnector::getSpeed() 
{
	return 0.0;
}
