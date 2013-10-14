class QgsCodeEditorPython: QgsCodeEditor
{
%TypeHeaderCode
#include <qgscodeeditorpython.h>
%End

  public:
    QgsCodeEditorPython( QWidget *parent = 0, const QList<QString> &filenames = QList<QString>() );
    ~QgsCodeEditorPython();

    void setTitle( QString );

    void loadAPIs(const QList<QString> &filenames );

  private:
    void setSciLexerPython();
};
