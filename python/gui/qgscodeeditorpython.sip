class QgsCodeEditorPython: QgsCodeEditor
{
%TypeHeaderCode
#include <qgscodeeditorpython.h>
%End

  public:
    QgsCodeEditorPython( QWidget *parent = 0 );
    ~QgsCodeEditorPython();

    void setTitle( QString );

  private:
    void setSciLexerPython();
};
