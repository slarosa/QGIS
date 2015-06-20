class QgsSplashScreen : QSplashScreen
{
%TypeHeaderCode
#include <qgssplashscreen.h>
%End

  public:
    QgsSplashScreen( const QPixmap &pixmap = QPixmap(), QWidget *parent = 0 );
    QProgressBar *mProgress;

    void setProgressValue( int value );
    void setImage( const QPixmap &pixmap );

  public slots:
    void progressBarUpdated( int value );

  protected:
    void drawContents( QPainter *painter );

};

