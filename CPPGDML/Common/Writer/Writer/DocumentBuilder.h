// -*- C++ -*-
// $Id: DocumentBuilder.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_WRITER_DOCUMENTBUILDER_H
#define GDML_WRITER_DOCUMENTBUILDER_H 1

#include <string>
#include <iosfwd>
#include <memory>

namespace gdml
{
  namespace writer
  {    
    class Element;
    class Document;

    class DefinitionsCursor;
    class MaterialsCursor;
    class SolidsCursor;
    class StructureCursor;
    class SetupCursor;

    struct BuilderSetup;
    
    /**
     * @class DocumentBuilder DocumentBuilder.h Writer/DocumentBuilder.h
     * The utility class to help building the GDML documents.
     * It exposes GDML document manipulation interface and allows to
     * manipulate all parts of GDML document in an isolated fashion
     * according to the GDML XML Schema. It does it by exposing different
     * interfaces at each GDML context level.
     *
     * @author Radovan Chytracek, CERN IT/DB, LCG AA
     * @date 09/06/2004
     */
    class DocumentBuilder
    {
      public:
        /// Default constructor, default output stream is std::cout
        explicit DocumentBuilder();
        /// Constructor
        /// @param outFileName If the file name is "" the default output stream becomes std::cout
        explicit DocumentBuilder( const std::string& outFileName );
        /// Constructor
        /// @param outFileStream Reference to a user supplied valid output stream
        explicit DocumentBuilder( std::ostream& outFileStream );
        /// Destructor
        ~DocumentBuilder();

        /// Open a new document. The output stream is associated with the document as given to
        /// constructor or the last DocumentBuilder::WriteDocument() call. If calling on the
        /// previously used document that will be reset.
        /// @see DocumentBuilder::ResetDocument()
        void OpenDocument();
        /// Write the current document to the associated (file) stream.
        /// @param newFileName     If the file name is "" or empty than the existing output stream is used.
        /// @param writeAll        If true all valid tags in the document will be written out
        ///                        else the tags without attributes and content will be ignored.
        /// @throws std::exception If there is a problem with either (non intialized) document
        ///                        or output stream.
        void WriteDocument( const std::string& newFileName="", bool writeAll=true );
        /// The same as above but accepts direct reference to a valid output stream
        /// @param newStream       User supplied valid instance of std::ostream class
        /// @param writeAll        If true all valid tags in the document will be written out
        ///                        else the tags without attributes and content will be ignored.
        /// @throws std::exception If there is a problem with either (non intialized) document
        ///                        or output stream.
        void WriteDocument( std::ostream& newStream, bool writeAll=true );
        /// Cleans all what's been done so far on a given document. Document becomes empty.
        /// Output stream remains the same as given by the constructor or the last call to
        /// DocumentBuilder::WriteDocument()
        void ResetDocument();
        /// Flushes the outpur stream and releases the document. Document is not usable after this call.
        /// One has to re-create the document of this builder instance by call to
        /// DocumentBuilder::OpenDocument() method
        void CloseDocument();

        /// Return the cursor for inserting GDML definitons
        DefinitionsCursor& getDefinitionsCursor();
        /// Return the cursor for inserting GDML materials
        MaterialsCursor& getMaterialsCursor();
        /// Return the cursor for inserting GDML solids
        SolidsCursor& getSolidsCursor();
        /// Return the cursor for inserting GDML volume structure
        StructureCursor& getStructureCursor();
        /// Return the cursor for inserting GDML geometry setups
        SetupCursor& getSetupCursor();

				/// Sets GDML schema file location
				void setSchemaLocation( const std::string& url );
        
      protected:
        /// Prepares the output stream for the document
        /// May throw an std::run_time exception if there is a problem to initialize the output stream
        /// @param newFileName     If the file name is "" or empty than the existing output stream is used.
        /// @throws std::exception If there is a problem with either (non intialized) document
        ///                        or output stream.
        void InitializeStream( const std::string& newFileName );
        /// Prepares the output stream for the document
        /// May throw an std::run_time exception if there is a problem to initialize the output stream
        /// @param newStream       User supplied valid instance of std::ostream class
        /// @throws std::exception If there is a problem with either (non intialized) document
        ///                        or output stream.
        void InitializeStream( std::ostream& newStream );
        
      private:
        /// Hidden copy constructor
        DocumentBuilder( const DocumentBuilder& );
        /// Hidden assignment operator
        const DocumentBuilder& operator =( const DocumentBuilder& );

      private:
        Document*                   m_doc;    ///< The actual document being built
        std::auto_ptr<BuilderSetup> m_setup;  ///< Internal output stream management
        DefinitionsCursor*          m_defcur; ///< The definitions insertion cursor
        MaterialsCursor*            m_matcur; ///< The materials insertion cursor
        SolidsCursor*               m_sldcur; ///< The solids insertion cursor
        StructureCursor*            m_volcur; ///< The solids insertion cursor
        SetupCursor*                m_setcur; ///< The setups insertion cursor
    };
  }
}

#endif // GDML_WRITER_DOCUMENTBUILDER_H
