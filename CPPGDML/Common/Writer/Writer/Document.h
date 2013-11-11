//-*- C++ -*-
// $Id: Document.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_DOCUMENT_H
#define GDML_WRITER_DOCUMENT_H 1

#include <string>
#include <vector>
#include <iosfwd>

namespace gdml
{
  namespace writer
  {
    class Element;
    class DocumentBuilder;
    
    typedef std::vector<Element> Setups;
    
    /**
     * The class represents a GDML data file.
     * At present it has fixed set of sections according to the GDML Schema.
     * GDML document holds GDML modeled data with the possibility to write
     * the data to an associated stream. This class does not prescribe how the
     * GDML data will be entered. This is the task for @see DocumentBuilder class.
     * NOTE: The GDML data file is written using UTF-8 byte encoding.
     */
    class Document
    {
      public:
        friend class DocumentBuilder;
        
      public:
        /// Constructor
        explicit Document( std::ostream& outstream );
        /// Destructor
        virtual ~Document();
        /// Pre-create GDML document structure
        void Initialize();
        /// Free the document data structures
        void Release();
        /// Return the document top-level element
        const Element& getDocument() const;        
        /// Writes document to the stream specified in constructor
        /// May throw std::logic_error exception if GDML validity constraints
        /// are corrupted
        void Write( bool writeAll=true ) const;
				/// Sets GDML schema location
				/// @param url The URL pointing to the desired GDML schema file
				void setSchemaLocation( const std::string& url );

      protected:
        /// Return the document top-level element
        Element& getDocument();

      private:
        /// Hidden copy constructor
        Document( const Document& );
        /// Hidden assignment operator
        const Document& operator =( const Document& );
        
      private:
        Element*      m_document;    ///< Top level document element(gdml)
        std::ostream& m_stream;      ///< The output stream
        bool          m_initialized; ///< Flag signaling state of the document
				std::string   m_schemaURL;   ///< Location of the GDML schema file
    };
  }
}

#endif // GDML_WRITER_DOCUMENT_H
