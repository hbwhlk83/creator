/*
 * LanguageManager.h
 *
 *  Created on: 2016-04-25
 *      Author: liukai
 */

#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

class LanguageManager {
public:
	static LanguageManager* getInstance();
	static void deleteInstance();

	void installTranslators();
private:
	LanguageManager();
	~LanguageManager();



public:
	static LanguageManager* m_LagInstace;
};

#endif//LANGUAGEMANAGER_H