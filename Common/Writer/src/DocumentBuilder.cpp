#include "Writer/DocumentBuilder.h"

#include "Writer/Element.h"
#include "Writer/EditableDocument.h"
#include "Writer/DefinitionsCursor.h"
#include "Writer/MaterialsCursor.h"
#include "Writer/SolidsCursor.h"
#include "Writer/StructureCursor.h"
#include "Writer/SetupCursor.h"

#include <iostream>
#include <fstream>

namespace gdml
{
  namespace writer
  {
    struct BuilderSetup
    {
        explicit BuilderSetup( const std::string& fName      = "",
                               std::ostream*      fStreamPtr = 0,
                               std::filebuf*      fBuf       = 0 )
          : outFileName( fName ),
            outstream( fStreamPtr ),
            outfile( fBuf )
        {
        }
        
        ~BuilderSetup()
        {          
          // Relase the output file buffer
          if( outfile != 0 )
          {
            // Finalize the output stream buffer if open
            if( outfile->is_open() )
              outfile->close();

            delete outfile;
            outfile = 0;
          }
          
          if( outstream != 0 )
          {
            delete outstream;
            outstream = 0;
          }
        }
        
        /// Output file name
        std::string     outFileName;
        /// Output stream
        std::ostream*   outstream;
        /// Output stream
        std::filebuf*   outfile;
    };

    DocumentBuilder::DocumentBuilder()
      : m_doc( 0 ),
        m_setup( new BuilderSetup ),
        m_defcur( 0 ),
        m_matcur( 0 ),
        m_sldcur( 0 ),
        m_volcur( 0 ),
        m_setcur( 0 )
    {
      m_setup->outstream = new std::ostream( std::cout.rdbuf() );
    }
    
    DocumentBuilder::DocumentBuilder( const std::string& outFileName )
      : m_doc( 0 ),
        m_setup( new BuilderSetup( outFileName, 0, 0 ) ),
        m_defcur( 0 ),
        m_matcur( 0 ),
        m_sldcur( 0 ),
        m_volcur( 0 ),
        m_setcur( 0 )
    {
      if( !m_setup->outFileName.empty() ) 
      {
        // Try to open the file
        m_setup->outfile   = new std::filebuf();
        m_setup->outstream = new std::ostream( m_setup->outfile );

        m_setup->outfile->open( m_setup->outFileName.c_str(),
                                std::ios::out | std::ios::trunc );
      }
      else
      {
        // Go via std::cout
        m_setup->outstream = new std::ostream( std::cout.rdbuf() );
      }
    }
    
    DocumentBuilder::DocumentBuilder( std::ostream& outFileStream )
      : m_doc( 0 ),
        m_setup( new BuilderSetup ),
        m_defcur( 0 ),
        m_matcur( 0 ),
        m_sldcur( 0 ),
        m_volcur( 0 ),
        m_setcur( 0 )
    {
      m_setup->outstream = new std::ostream( outFileStream.rdbuf() );
    }

    DocumentBuilder::~DocumentBuilder()
    {
      // Drop the current document
      if( m_doc != 0 )
        delete m_doc;
      m_doc = 0;      

      // Clean cursors
      if( m_defcur != 0 )
        delete m_defcur;
      if( m_matcur != 0 )
        delete m_matcur;
      if( m_sldcur != 0 )
        delete m_sldcur;
      if( m_volcur != 0 )
        delete m_volcur;
      if( m_setcur != 0 )
        delete m_setcur;
    }

    void DocumentBuilder::OpenDocument()
    {
      if( m_doc == 0 )
        m_doc = new EditableDocument( *m_setup->outstream );
      else
        ResetDocument();
    }

    void DocumentBuilder::WriteDocument( const std::string& newFileName, bool writeAll )
    {
      // Prepare the output stream
      if( newFileName != m_setup->outFileName && !newFileName.empty() )
        InitializeStream( newFileName );
      m_doc->Write( writeAll );
    }
    
    void DocumentBuilder::WriteDocument( std::ostream& newStream, bool writeAll )
    {
      // First prepare the output stream
      InitializeStream( newStream );
      m_doc->Write( writeAll );
    }

    void DocumentBuilder::ResetDocument()
    {
      // Simply ...
      m_doc->Release();
      m_doc->Initialize();
    }

    void DocumentBuilder::CloseDocument()
    {      
      m_doc->Release();
      delete m_doc;
      m_doc = 0;
    }

    // Cursors
    DefinitionsCursor& DocumentBuilder::getDefinitionsCursor()
    {
      EditableDocument* ed = dynamic_cast<EditableDocument*>( m_doc );

      EditableDocumentRegistry& edreg       = ed->getRegistry();
      Element& definitions =
        const_cast<Element&>( ed->getDocument().getElementByName("define") );
      
      m_defcur = new DefinitionsCursor( definitions, edreg );
      
      return( *m_defcur );
    }

    MaterialsCursor& DocumentBuilder::getMaterialsCursor()
    {
      EditableDocument* ed            = dynamic_cast<EditableDocument*>( m_doc );
      EditableDocumentRegistry& edreg = ed->getRegistry();
      Element& materials              =
        const_cast<Element&>( ed->getDocument().getElementByName("materials") );
      
      m_matcur = new MaterialsCursor( materials, edreg );
      
      return( *m_matcur );
    }

    SolidsCursor& DocumentBuilder::getSolidsCursor()
    {
      EditableDocument* ed            = dynamic_cast<EditableDocument*>( m_doc );
      EditableDocumentRegistry& edreg = ed->getRegistry();
      Element& solids                 =
        const_cast<Element&>( ed->getDocument().getElementByName("solids") );
      
      m_sldcur = new SolidsCursor( solids, edreg );
      
      return( *m_sldcur );
    }

    StructureCursor& DocumentBuilder::getStructureCursor()
    {
      EditableDocument* ed            = dynamic_cast<EditableDocument*>( m_doc );
      EditableDocumentRegistry& edreg = ed->getRegistry();
      Element& structure              = const_cast<Element&>( ed->getDocument().getElementByName("structure") );
      
      m_volcur = new StructureCursor( structure, edreg );
      
      return( *m_volcur );
    }
    
    SetupCursor& DocumentBuilder::getSetupCursor()
    {
      EditableDocument* ed            = dynamic_cast<EditableDocument*>( m_doc );
      EditableDocumentRegistry& edreg = ed->getRegistry();
      Element& setups                 = const_cast<Element&>( ed->getDocument() );
      
      m_setcur = new SetupCursor( setups, edreg );
      
      return( *m_setcur );
    }

    void DocumentBuilder::setSchemaLocation( const std::string& url )
		{
			/// Forward to the document
			m_doc->setSchemaLocation( url );
		}
		
    void DocumentBuilder::InitializeStream( const std::string& newFileName )
    {
      if( newFileName.empty() )
      {
        m_setup->outFileName = "";
        
        if( m_setup->outstream == 0 )        
          m_setup->outstream = new std::ostream( std::cout.rdbuf() );          
      }
      else
      {
        // First make sure the old buffer is properly closed
        if( m_setup->outfile != 0 )
        {
          // Ooops, the buffer has been initialized
          if( m_setup->outfile->is_open() )
            m_setup->outfile->close();
          
          delete m_setup->outfile;
          m_setup->outfile = 0;
        }
        
        // Re-open the file output stream
        m_setup->outFileName = newFileName;
        m_setup->outfile     = new std::filebuf();

        m_setup->outfile->open( newFileName.c_str(), std::ios::out | std::ios::trunc );
        
        m_setup->outstream->rdbuf( m_setup->outfile );
      }

      // Check if the existing stream is OK
      if( !m_setup->outstream->good() )
      {
        std::string msg = "Problem to initialize GDML output stream >>" + m_setup->outFileName + "<<";
        throw std::ios::failure( msg );
      }
    }
    
    void DocumentBuilder::InitializeStream( std::ostream& newStream )
    {      
      // We believe user he's passed us a valid stream, but...
      if( !newStream.good() )
      {
        std::string msg = "Attempt to set an invalid GDML output stream ";
        throw std::ios::failure( msg );
      }
      else
      {
        // Streams seems fine, but first finalize the current stream
        
        // Relase the output file buffer
        if( m_setup->outfile != 0 )
        {
          // Finalize the output stream buffer if open
          if( m_setup->outfile->is_open() )
            m_setup->outfile->close();

          delete m_setup->outfile;
          m_setup->outfile = 0;
        }

        if( m_setup->outstream == 0 )
        {
          m_setup->outstream = new std::ostream( newStream.rdbuf() );
        }
        else
        {
          m_setup->outstream->rdbuf( newStream.rdbuf() );
        }
      }
    }
  }
}
