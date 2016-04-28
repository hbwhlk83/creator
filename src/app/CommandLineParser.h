/*
 * CommandLineParser.h
 *
 *  Created on: 2016-04-25
 *      Author: liukai
 */

#include <QStringList>

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

class CommandLineParser {
public:

	CommandLineParser() {};
	bool parse(const QStringList &arguments);
};


#endif//COMMANDLINEPARSER_H