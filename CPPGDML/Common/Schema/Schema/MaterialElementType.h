// -*- C++ -*-
// $Id: MaterialElementType.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_MATERIALELEMENTTYPE_H
#define GDML_SCHEMA_MATERIALELEMENTTYPE_H 1

#include "ContentGroup.h"
#include "MaterialType.h"
#include "DorDref.h"
#include "atom.h"

class AtomOrFraction : public ContentChoice
{
  public:
    AtomOrFraction() : isAtom( false )
    {
    }
    ~AtomOrFraction()
    {
    }
    const SAXObject* get_content() const
    {
      const SAXObject* so;
      if( isAtom )
        so = this;
      else
        so = &m_fractions;
      return so;
    }

    void set_content( const std::string& tag, SAXObject* so )
    {
      if( !isAtom ) {
        ContentGroup::ContentItem ci = {tag,so};
        if( tag == "fraction" ) {
          // Switch to sequence content model
          m_fractions.add_content( ci );
        } else if( tag == "atom" ) {
          ContentChoice::set_content( ci );
          isAtom = true;
          // No more updates should happen from now on....
        }
      }
    }

  private:
    bool isAtom;
    ContentSequence m_fractions;
};

class MaterialElementType : public MaterialType
{
  public:
    MaterialElementType() : m_density( 0 )
    {
    }
    virtual ~MaterialElementType()
    {
      if( m_density != 0 )
        delete m_density;
    }
    const std::string& get_N() const
    {
      return m_N;
    }
    const std::string& get_Z() const
    {
      return m_Z;
    }
    const SAXObject* get_AtomOrFraction() const
    {
      return m_aorf.get_content();
    }
    const SAXObject* get_DorDref() const
    {
      const SAXObject* so = 0;
      if( m_density != 0 ) {
        so = m_density->get_content();
      }
      return so;
    }
  
    void set_N( std::string& n )
    {
      m_N = n;
    }
    void set_Z( std::string& z )
    {
      m_Z = z;
    }
    void set_AtomOrFraction( const std::string& tag, SAXObject* so )
    {
      m_aorf.set_content( tag, so );
    }
    void set_DorDref( const std::string& tag, SAXObject* so )
    {
      if( !m_density ) {
        m_density = new DorDref;
      }
      m_density->set_content( tag, so);
    }
  
  private:
    DorDref*        m_density;
    AtomOrFraction  m_aorf;
    std::string     m_N;
    std::string     m_Z;
};

#endif // GDML_SCHEMA_MATERIALELEMENTTYPE_H
