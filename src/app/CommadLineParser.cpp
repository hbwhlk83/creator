/*
 * CommadLineParser.cpp
 *
 *  Created on: 2016-04-25
 *      Author: liukai
 */

#include "CommandLineParser.h"

bool CommandLineParser::parse(const QStringList &arguments) {
	if (arguments.length() == 0) {
		return false;
	}

	QStringList todo = arguments;
	QMutableStringListIterator it(todo);
	bool testOptionProvided = false;
	while (it.hasNext()) {
		const QString &arg = it.next();
	}

	return true;
}
