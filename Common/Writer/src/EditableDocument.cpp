#include "Writer/EditableDocument.h"
#include "Writer/EditableDocumentRegistry.h"

namespace gdml
{
  namespace writer
  {
    EditableDocument::EditableDocument( std::ostream& outStream )
      : Document( outStream ),
        m_reg( new EditableDocumentRegistry() )
    {
    }

    EditableDocument::~EditableDocument()
    {
      delete m_reg;
    }

    Element& EditableDocument::getDocument()
    {
      return Document::getDocument();
    }

    EditableDocumentRegistry& EditableDocument::getRegistry()
    {
      return *m_reg;
    }
  }
}
