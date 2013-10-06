class QgsCodeEditorPython: QgsCodeEditor
{
%TypeHeaderCode
#include <qgscodeeditorpython.h>
%End

  public:
    QgsCodeEditorPython( QWidget *parent = 0 );
    ~QgsCodeEditorPython();

  private:
    void setSciLexerPython();
};
