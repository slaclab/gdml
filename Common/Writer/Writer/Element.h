//-*- C++ -*-
// $Id: Element.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_ELEMENT_H
#define GDML_WRITER_ELEMENT_H 1

#include <iosfwd>

#include <string>
#include <map>
#include <vector>

namespace gdml
{
  namespace writer
  {
    // Forward declaration so the std::vector instantiation succeeds
    class Element;

    /// name-value pairs represent XML attributes
    typedef std::map< std::string , std::string > Attributes;
    typedef std::vector<Element>                  ElementContent;

    /**
     * Element class representing the XML data object before being serialized to
     * XML by GDML writer.
     *
     * NOTE: No check is done that the internak structure of this XML element is
     * valid according to a DTDT or XML Schema. This is left to the client application
     * to ensure the valid element content and the list of its attributes.
     */
    class Element
    {
      public:
        /// Default constructor
        explicit Element();
        /// Empty XML element constructor
        explicit Element( const std::string& tagName );
        /// Empty XML element with attributes only constructor
        explicit Element( const std::string& tagName,
                          const Attributes& attributes );
        /// XML element with a content constructor and no attributes
        explicit Element( const std::string& tagName,
                          const ElementContent& content );
        /// XML element with attributes and content constructor
        explicit Element( const std::string& tagName,
                          const Attributes& attributes,
                          const ElementContent& content );
        /// Destructor
        virtual ~Element();
        
        /// Add some attributes into element, overwrites by default!
        void addAttributes( const Attributes& attrs, bool overwrite=true );
        
        /// Add a single attribute into element, overwrites by default!
        void addAttribute( const std::string& name,
                           const std::string  value,
                           bool               overwrite=true );
        
        /// Add some children into element, will be added at the end
        void addChildren( const ElementContent& children );
        
        /// Add a single child into element, optionally specifying the insertion position
        /// and return its reference
        ElementContent::const_iterator addChild( const Element& child, size_t pos );

        /// Add a single child into element at the end of children sequence
        /// and return its reference
        ElementContent::iterator appendChild( const Element& child );

        /// Returns true if not attributes neither no content
        bool empty() const;

        /// Return true if at least one attribute present
        bool hasAttributes() const;

        /// Return true if at least one child element present
        bool hasContent() const;

        /// Return the tag name of the element
        const std::string& name() const;
        
        /// Return the attributes collection, possibly empty
        const Attributes& getAttributes() const;

        /// Return the children of this element
        const ElementContent& getContent() const;

        /// Return the child by tag name, this level only, does not go deep
        /// If not found return an empty string
        const Element& getElementByName( const std::string& tagName ) const;

        /// Return the number of attributes
        size_t numOfAttributes() const;

        /// Return the number of child elements
        size_t numOfElements() const;        
        
        /// Write the XML form into the specified std::ostream stream
        /// If ignoreEmptyTags is true the immediate empty children are skipped
        /// This is useful at the top level to leave out the irrelevant tags
        void toXml( std::ostream& os, bool ignoreEmptyTags=false, bool indent=true );
        
      private:
        // For the time being we rely on the compiler defined copy constructor and assignment
        // Hide the copy constructor
        //Element( const Element& );
        //  Hide the assignment operator
        //const Element& operator =( const Element& );

        /// Build and return XML start tag of formatting
        /// @param indent Insert indentation spaces according to the m_indentation value
        std::string startTag( bool indent ) const;
        /// Build and return XML end tag of formatting
        /// @param indent Insert indentation spaces according to the m_indentation value
        std::string endTag( bool indent ) const;

        /// Return indentation value for the 
        unsigned getIndentation() const
        {
          return m_indentation;
        }

        /// Set indentation width and return the old indentation value
        /// @param indentation Number of indentation spaces
        unsigned setIndentation( unsigned indentation )
        {
          unsigned old = m_indentation;
          m_indentation = indentation;
          return old;
        }

        unsigned m_indentation;               ///< The indentation used for serializing into XML
        
      private:
        std::string          m_tagName;       ///< XML tag name
        Attributes           m_attributes;    ///< XML tag attributes
        ElementContent       m_content;       ///< Sequence of XML elements in the tag's content model
    };
  }
}

#endif // GDML_WRITER_ELEMENT_H
