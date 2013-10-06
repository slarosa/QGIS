class QgsCodeEditor: QsciScintilla
{
%TypeHeaderCode
#include <qgscodeeditor.h>
%End

  public:
    QgsCodeEditor( QWidget *parent = 0, QString title = "" );
    ~QgsCodeEditor();

  private:
    void setSciWidget();
};
