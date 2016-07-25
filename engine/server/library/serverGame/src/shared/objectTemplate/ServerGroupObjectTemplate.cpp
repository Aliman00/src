//========================================================================
//
// ServerGroupObjectTemplate.cpp
//
//IMPORTANT: Any code between //@BEGIN TFD... and //@END TFD... will be
//overwritten the next time the template definition is compiled. Do not
//make changes to code inside these blocks.
//
// copyright 2001 Sony Online Entertainment
//
//========================================================================

#include "serverGame/FirstServerGame.h"
#include "ServerGroupObjectTemplate.h"

#include "serverGame/GroupObject.h"
#include "sharedFile/Iff.h"
#include "sharedObject/ObjectTemplate.h"
#include "sharedObject/ObjectTemplateList.h"

//@BEGIN TFD TEMPLATE REFS
//@END TFD TEMPLATE REFS
#include <stdio.h>

const std::string DefaultString("");
const StringId DefaultStringId("", 0);
const Vector DefaultVector(0, 0, 0);
const TriggerVolumeData DefaultTriggerVolumeData;

bool ServerGroupObjectTemplate::ms_allowDefaultTemplateParams = true;

/**
 * Class constructor.
 */
ServerGroupObjectTemplate::ServerGroupObjectTemplate(const std::string & filename)
//@BEGIN TFD INIT
	: ServerUniverseObjectTemplate(filename)
	, m_versionOk(true)
	, m_templateVersion(0)
	//@END TFD INIT
{
}	// ServerGroupObjectTemplate::ServerGroupObjectTemplate

/**
 * Class destructor.
 */
ServerGroupObjectTemplate::~ServerGroupObjectTemplate()
{
	//@BEGIN TFD CLEANUP
	//@END TFD CLEANUP
}	// ServerGroupObjectTemplate::~ServerGroupObjectTemplate

/**
 * Static function used to register this template.
 */
void ServerGroupObjectTemplate::registerMe(void)
{
	ObjectTemplateList::registerTemplate(ServerGroupObjectTemplate_tag, create);
}	// ServerGroupObjectTemplate::registerMe

/**
 * Creates a ServerGroupObjectTemplate template.
 *
 * @return a new instance of the template
 */
ObjectTemplate * ServerGroupObjectTemplate::create(const std::string & filename)
{
	return new ServerGroupObjectTemplate(filename);
}	// ServerGroupObjectTemplate::create

/**
 * Returns the template id.
 *
 * @return the template id
 */
Tag ServerGroupObjectTemplate::getId(void) const
{
	return ServerGroupObjectTemplate_tag;
}	// ServerGroupObjectTemplate::getId

/**
 * Returns this template's version.
 *
 * @return the version
 */
Tag ServerGroupObjectTemplate::getTemplateVersion(void) const
{
	return m_templateVersion;
} // ServerGroupObjectTemplate::getTemplateVersion

/**
 * Returns the highest version of this template or it's base templates.
 *
 * @return the highest version
 */
Tag ServerGroupObjectTemplate::getHighestTemplateVersion(void) const
{
	if (m_baseData == nullptr)
		return m_templateVersion;
	const ServerGroupObjectTemplate * base = dynamic_cast<const ServerGroupObjectTemplate *>(m_baseData);
	if (base == nullptr)
		return m_templateVersion;
	return std::max(m_templateVersion, base->getHighestTemplateVersion());
} // ServerGroupObjectTemplate::getHighestTemplateVersion

/**
 * Creates a new object from this template.
 *
 * @return the object
 */
Object * ServerGroupObjectTemplate::createObject(void) const
{
	return new GroupObject(this);
}	// ServerGroupObjectTemplate::createObject

//@BEGIN TFD

/**
 * Loads the template data from an iff file. We should already be in the form
 * for this template.
 *
 * @param file		file to load from
 */
void ServerGroupObjectTemplate::load(Iff &file)
{
	static const int MAX_NAME_SIZE = 256;
	char paramName[MAX_NAME_SIZE];

	if (file.getCurrentName() != ServerGroupObjectTemplate_tag)
	{
		ServerUniverseObjectTemplate::load(file);
		return;
	}

	file.enterForm();
	m_templateVersion = file.getCurrentName();
	if (m_templateVersion == TAG(D, E, R, V))
	{
		file.enterForm();
		file.enterChunk();
		std::string baseFilename;
		file.read_string(baseFilename);
		file.exitChunk();
		const ObjectTemplate *base = ObjectTemplateList::fetch(baseFilename);
		DEBUG_WARNING(base == nullptr, ("was unable to load base template %s", baseFilename.c_str()));
		if (m_baseData == base && base != nullptr)
			base->releaseReference();
		else
		{
			if (m_baseData != nullptr)
				m_baseData->releaseReference();
			m_baseData = base;
		}
		file.exitForm();
		m_templateVersion = file.getCurrentName();
	}
	if (getHighestTemplateVersion() != TAG(0, 0, 0, 0))
	{
		m_versionOk = false;
	}

	file.enterForm();

	file.enterChunk();
	int paramCount = file.read_int32();
	file.exitChunk();
	UNREF(paramName);
	UNREF(paramCount);

	file.exitForm();
	ServerUniverseObjectTemplate::load(file);
	file.exitForm();
	return;
}	// ServerGroupObjectTemplate::load

//@END TFD