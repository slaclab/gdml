#include "Writer/Element.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace gdml
{
  namespace writer
  {
    Element::Element()
      : m_indentation( 0 ),
        m_tagName("")
    {
    }
    
    Element::Element( const std::string& tagName )
      : m_indentation( 0 ),
        m_tagName(tagName)
    {
    }
    
    Element::Element( const std::string& tagName,
                      const Attributes&  attributes )
      : m_indentation( 0 ),
        m_tagName(tagName),
        m_attributes( attributes )
    {
    }

    Element::Element( const std::string&    tagName,
                      const ElementContent& content )
      : m_indentation( 0 ),
        m_tagName(tagName),
        m_content( content )
    {
    }
    
    Element::Element( const std::string&    tagName,
                      const Attributes&     attributes,
                      const ElementContent& content )
      : m_indentation( 0 ),
        m_tagName(tagName),
        m_attributes( attributes ),
        m_content( content )
    {
    }

    Element::~Element()
    {
    }

    void Element::addAttributes( const Attributes& attrs, bool overwrite )
    {
      if( !attrs.empty() )
      {
        for( Attributes::const_iterator cit = attrs.begin();
             cit != attrs.end();
             ++cit )
        {
          if( overwrite )
            //m_attributes.insert( (*cit) );
            m_attributes[(*cit).first] = (*cit).second;
          else
            if( m_attributes.find( (*cit).first ) == m_attributes.end() )
              m_attributes.insert( (*cit) );
        }
      }      
    }
        
    void Element::addAttribute( const std::string& name,
                                const std::string  value,
                                bool               overwrite )
    {
      if( overwrite )
//         m_attributes.insert( std::make_pair(name, value) );
        m_attributes[name] = value;
      else
        if( m_attributes.find( name ) == m_attributes.end() )
          m_attributes.insert( std::make_pair(name, value) );
    }
    
    void Element::addChildren( const ElementContent& children )
    {
      if( !children.empty() )
        m_content.insert( m_content.end(), children.begin(), children.end() );
    }
        
    ElementContent::const_iterator Element::addChild( const Element& child, size_t pos )
    {      
      if( (long)pos >= 0 && pos <= m_content.size() )
      {
        ElementContent::iterator cit = m_content.begin(); // Start at the beginning of the content
        cit += pos;                                       // Isn't it a bit tricky?
        m_content.insert( cit, child );                   // Insert at the given position
        --cit;                                            // The new element has been inserted
        return cit;                                       // before the current pos
      }
      
      return m_content.end();
    }

    ElementContent::iterator Element::appendChild( const Element& child )
    {
      m_content.push_back( child );
      return( --m_content.end() );
    }

    bool Element::empty() const
    {
      return !hasAttributes() && !hasContent();
    }

    bool Element::hasAttributes() const
    {
      return !m_attributes.empty();
    }
    
    bool Element::hasContent() const
    {
      return !m_content.empty();
    }

    const std::string& Element::name() const
    {
      return m_tagName;
    }
        
    const Attributes& Element::getAttributes() const
    {
      return m_attributes;
    }

    const ElementContent& Element::getContent() const
    {
      return m_content;
    }

    static Element notFound( "not_found" );

    const Element& Element::getElementByName( const std::string& tagName ) const
    {      
      ElementContent::const_iterator cit = m_content.begin();

      while( cit != m_content.end() )
      {
        if( (*cit).m_tagName == tagName )
          break;
        
        ++cit;
      }

      if( cit == m_content.end() )
        throw std::logic_error( "Element by name " + tagName + " not found!" );

      return (*cit);
    }
    
    size_t Element::numOfAttributes() const
    {
      return m_attributes.size();
    }
    
    size_t Element::numOfElements() const
    {
      return m_content.size();
    }
    
    void Element::toXml( std::ostream& os, bool ignoreEmptyTags, bool indent )
    {
      if( m_tagName.empty() )
      {
        std::string msg = "Empty tag name!";
        // Invalid! A tag has to have a name
        throw std::logic_error( msg );
      }
      
      os << startTag( indent );

      // In case there are children ask them to do this themselves
      if( hasContent() )
      {
        for( ElementContent::iterator cit = m_content.begin();
             cit != m_content.end();
             cit++ )
        {
          // Skip empty tag if requested
          if( ignoreEmptyTags && (*cit).empty() )
            continue;
          
          os << std::endl;
          
          (*cit).setIndentation( m_indentation + 1 );
          (*cit).toXml( os, ignoreEmptyTags, indent );
        }
      }

      os << endTag( indent );
    }

    std::string Element::startTag( bool indent ) const
    {
      std::string ind = "";
      
      if( indent && m_indentation > 0 )
        ind = std::string( m_indentation, ' ' );
      
      // Prepare tag opening
      std::string temp( ind + "<" + m_tagName );
      
      if( hasAttributes() )
      {
        // Add space to separate tag name from attributes
        temp += " ";
        
        // Append all the attributes
        Attributes::const_iterator cit = m_attributes.begin();
        while( cit != m_attributes.end() )
        {
          temp += (*cit).first + "=\"" + (*cit).second + "\" ";
          ++cit;
        }
      }
      
      if( hasContent() )
        // Finish tag opening
        temp += ">";
      
      return temp;
    }
    
    std::string Element::endTag( bool indent ) const
    {
      std::string ind = "";
      
      if( indent && m_indentation > 0 )
        ind = std::string( m_indentation, ' ' );
      
      // By this we generate shorter XML
      if( this->hasContent() )
      {
        return( "\n" + ind + "</" + m_tagName + ">" );
      }
      else
      {
        return( "/>" );
      }
    }    
  }
}
