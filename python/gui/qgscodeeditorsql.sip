class QgsCodeEditorSQL: QgsCodeEditor
{
%TypeHeaderCode
#include <qgscodeeditorsql.h>
%End

  public:
    QgsCodeEditorSQL( QWidget *parent = 0 );
    ~QgsCodeEditorSQL();

  private:
    void setSciLexerSQL();
};
