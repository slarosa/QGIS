class QgsCodeEditorSQL: QgsCodeEditor
{
%TypeHeaderCode
#include <qgscodeeditorsql.h>
%End

  public:
    QgsCodeEditorSQL( QWidget *parent = 0 );
    ~QgsCodeEditorSQL();

    void setTitle( QString );

  private:
    void setSciLexerSQL();
};
