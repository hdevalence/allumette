/*
 * Copyright 2012 Henry de Valence <hdevalence@hdevalence.ca>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy 
 * defined in Section 14 of version 3 of the license.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QByteArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>

#include "AllumetteEngine.h"
#include "EImage.h"

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	QTextStream out(stdout);
	QStringList args = app.arguments();
	if (args.length() != 2) {
		out << "Usage: allumette-cli config.json";
		return -1;
	}
	QFile jsonFile(args[1]);
	if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		out << "Cannot open configuration file";
		return -1;
	}
	QByteArray json = jsonFile.readAll();
	// Just print it out rather than do anything,
	// to have something minimal to test the build system
	out << json;
	QJsonObject params = QJsonDocument::fromJson(json).object();
	AllumetteEngine engine(params);
	EImage i = engine.stack();
	return 0;
}

