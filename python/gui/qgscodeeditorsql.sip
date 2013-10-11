class QgsCodeEditorSQL: QgsCodeEditor
{
%TypeHeaderCode
#include <qgscodeeditorsql.h>
%End

  public:
    QgsCodeEditorSQL( QWidget *parent = 0 );
    ~QgsCodeEditorSQL();

    void setTitle( QString );

    void showMargin( bool withMargin );

    void showFolding( bool withFolding );

  private:
    void setSciLexerSQL();
};
