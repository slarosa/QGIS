class QgsCodeEditor: QsciScintilla
{
%TypeHeaderCode
#include <qgscodeeditor.h>
%End

  public:
    QgsCodeEditor( QWidget *parent = 0, QString title = "" , bool folding = false, bool margin = false );
    ~QgsCodeEditor();

    void enableMargin( bool folding );

    void enableFolding( bool margin );
};
