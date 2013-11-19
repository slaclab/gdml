// -*- C++ -*-
// $Id: MaterialMixtureType.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_MATERIALMIXTURETYPE_H
#define GDML_SCHEMA_MATERIALMIXTURETYPE_H 1

#include "MaterialType.h"
#include "DorDref.h"
#include "TorTref.h"
#include "PorPref.h"
#include "atom.h"

class MaterialMixtureType : public MaterialType
{
  public:
    MaterialMixtureType()
    {
    }
    virtual ~MaterialMixtureType()
    {
    }
    const std::string& get_Z() const
    {
      return m_Z;
    }
    const SAXObject* get_DorDref() const
    {
      return( m_density.get_content() );
    }
    ContentChoice* get_choice()
    {
      return &m_choice;
    }
    const ContentChoice* get_choice() const
    {
      return &m_choice;
    }
    void set_Z( const std::string& z )
    {
      m_Z = z;
    }
    void set_DorDref( const std::string& tag, SAXObject* so )
    {
      m_density.set_content( tag, so);
    }
    void set_choice( const std::string& tag, SAXObject* so )
    {
      ContentGroup::ContentItem ci = { tag, so };
      m_choice.set_content( ci );
    }
  
  private:
    DorDref         m_density;
    ContentChoice   m_choice;
    std::string     m_Z;
};

#endif // GDML_SCHEMA_MATERIALMIXTURETYPE_H
