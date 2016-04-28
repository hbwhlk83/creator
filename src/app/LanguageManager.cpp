/*
 * LanguageManager.cpp
 *
 *  Created on: 2016-04-25
 *      Author: liukai
 */

#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QCoreApplication>
#include "LanguageManager.h"

LanguageManager* LanguageManager::m_LagInstace = NULL;

LanguageManager::LanguageManager() {}

LanguageManager::~LanguageManager() {}

void LanguageManager::installTranslators() {
	QTranslator *appTranslator = new QTranslator();
	QTranslator *qtTranslator = new QTranslator();


	const QString resourceDir = QLibraryInfo::location(QLibraryInfo::TranslationsPath);

	const QString localSysName = QLocale::system().name();
	QString  translatorFileName = QLatin1String("LwpCreator_");
	translatorFileName += localSysName;
	if (appTranslator->load(translatorFileName, resourceDir))
		QCoreApplication::installTranslator(appTranslator);
	else 
		delete appTranslator;

	translatorFileName = QLatin1String("qt_");
	translatorFileName += localSysName;
	if (qtTranslator->load(translatorFileName, resourceDir))
		QCoreApplication::installTranslator(qtTranslator);
	else
		delete qtTranslator;
}

LanguageManager* LanguageManager::getInstance() {
	if (m_LagInstace == NULL) {
		m_LagInstace = new LanguageManager();
	}

	return m_LagInstace;
}

void LanguageManager::deleteInstance() {
	if (m_LagInstace != NULL) {
		delete m_LagInstace;
		m_LagInstace = NULL;
	}
}
