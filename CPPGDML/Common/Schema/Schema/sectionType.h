#ifndef SECTIONTYPE_H
#define SECTIONTYPE_H 1

#include "Saxana/SAXObject.h"

class sectionType : public SAXObject {
public:
	sectionType() {};
	virtual ~sectionType() {};

	virtual SAXObject::Type type()  { return SAXObject::element; }

	void set_zOrder(const std::string& zOrder) { m_zOrder = zOrder; }
	void set_zPosition(const std::string& zPosition) { m_zPosition = zPosition; }
	void set_xOffset(const std::string& xOffset) { m_xOffset = xOffset; }
	void set_yOffset(const std::string& yOffset) { m_yOffset = yOffset; }
	void set_scalingFactor(const std::string& scalingFactor) { m_scalingFactor = scalingFactor; }

	const std::string& get_zOrder() { return m_zOrder; }
	const std::string& get_zPosition() { return m_zPosition; }
	const std::string& get_xOffset() { return m_xOffset; }
	const std::string& get_yOffset() { return m_yOffset; }
	const std::string& get_scalingFactor() { return m_scalingFactor; }
private:
	std::string m_zOrder;
	std::string m_zPosition;
	std::string m_xOffset;
	std::string m_yOffset;
	std::string m_scalingFactor;
};

#endif
