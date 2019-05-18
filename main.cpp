#include <QCoreApplication>
#include <QtSql>
#include <iostream>
#include <QDebug>

#define q2c(string) string.toStdString()

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << QSqlDatabase::drivers();

    using namespace std;

    cout << "SkypeToSMS Bridge Prototype\n\n"
         << endl;

    // Test if Skype SQLite database is present at its default location
    if (QFile::exists("~/Documents/main.db"))
    {
        cout << "La base existe.\n"
             << endl;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    //db.setUserName("root");
    //db.setPassword("");
    db.setDatabaseName("~/.Skype/VAR_USER/main.db");
    bool b = db.open();

    if (b)
    {
        cout << "Open\n\n"
             << endl;
    }

    int i = 80;
    int n = 15;

    bool r = true;

    while (r)
    {
        // Collect new received messages
        QSqlQuery query;
        query.prepare("SELECT id, body_xml FROM Messages WHERE id > ? AND convo_id = VAR_CONVO_ID AND author = 'VAR_AUTHOR' ORDER BY id ASC");
        query.addBindValue(i);
        if (query.exec())
        {
            while (query.next())
            {
                std::cout << "\n"
                          << std::endl;
                i = query.value(0).toInt();
                std::cout << q2c(query.value(0).toString()) << std::endl;

                QString m = query.value(1).toString();
                // Process message
                m.remove(QRegExp("<ss type=\"[a-zA-Z]*\">"));
                m.remove(QRegExp("<quote[^><]*>"));
                m.remove(QRegExp("<e_m[^><]*/>"));
                m.remove("</quote>");
                m.remove("<legacyquote>");
                m.remove("</legacyquote>");
                m.remove("</ss>");
                m.replace("&quot;", "\"").replace("&apos;", "'").replace("&amp;", "&").replace("&euro;", "€").replace("&lt;", "<").replace("&gt;", ">").replace("&oelig;", "oe").replace("&Yuml;", "Y").replace("&nbsp;", "Space").replace("&iexcl;", "¡").replace("&cent;", "¢").replace("&pound;", "£").replace("&curren;", "¤").replace("&yen", "¥").replace("&brvbar;", "¦").replace("&sect;", "§").replace("&uml;", "¨").replace("&copy;", "©").replace("&ordf;", "ª").replace("&laquo;", "«").replace("&not;", "¬").replace("&shy;", "­").replace("&reg;", "®").replace("&masr;", "¯").replace("&deg;", "°").replace("&plusmn;", "±").replace("&sup2;", "²").replace("&sup3;", "³").replace("&acute;", "'").replace("&micro;", "µ").replace("&para;", "¶").replace("&middot;", "·").replace("&cedil;", "¸").replace("&sup1;", "¹").replace("&ordm;", "º").replace("&raquo;", "»").replace("&frac14;", "¼").replace("&frac12;", "½").replace("&frac34;", "¾").replace("&iquest;", "¿").replace("&Agrave;", "À").replace("&Aacute;", "Á").replace("&Acirc;", "Â").replace("&Atilde;", "Ã").replace("&Auml;", "Ä").replace("&Aring;", "Å").replace("&Aelig", "Æ").replace("&Ccedil;", "Ç").replace("&Egrave;", "È").replace("&Eacute;", "É").replace("&Ecirc;", "Ê").replace("&Euml;", "Ë").replace("&Igrave;", "Ì").replace("&Iacute;", "Í").replace("&Icirc;", "Î").replace("&Iuml;", "Ï").replace("&eth;", "Ð").replace("&Ntilde;", "Ñ").replace("&Ograve;", "Ò").replace("&Oacute;", "Ó").replace("&Ocirc;", "Ô").replace("&Otilde;", "Õ").replace("&Ouml;", "Ö").replace("&times;", "×").replace("&Oslash;", "Ø").replace("&Ugrave;", "Ù").replace("&Uacute;", "Ú").replace("&Ucirc;", "Û").replace("&Uuml;", "Ü").replace("&Yacute;", "Ý").replace("&thorn;", "Þ").replace("&szlig;", "ß").replace("&agrave;", "à").replace("&aacute;", "á").replace("&acirc;", "â").replace("&atilde;", "ã").replace("&auml;", "ä").replace("&aring;", "å").replace("&aelig;", "æ").replace("&ccedil;", "ç").replace("&egrave;", "è").replace("&eacute;", "é").replace("&ecirc;", "ê").replace("&euml;", "ë").replace("&igrave;", "ì").replace("&iacute;", "í").replace("&icirc;", "î").replace("&iuml;", "ï").replace("&eth;", "ð").replace("&ntilde;", "ñ").replace("&ograve;", "ò").replace("&oacute;", "ó").replace("&ocirc;", "ô").replace("&otilde;", "õ").replace("&ouml;", "ö").replace("&divide;", "÷").replace("&oslash;", "ø").replace("&ugrave;", "ù").replace("&uacute;", "ú").replace("&ucirc;", "û").replace("&uuml;", "ü").replace("&yacute;", "ý").replace("&thorn;", "þ").replace("&yuml;", "ÿ").replace("&quot;", "\"").replace("&amp;", "&").replace("&lsaquo;", "<").replace("&rsaquo;", ">");
                m.replace("\"", "\\\"");

                std::cout << q2c(m) << std::endl;

                // Send the message by SMS
                if (!m.isEmpty())
                {
                    m.insert(0, "echo \"");
                    m.append("\" | gammu --sendsms TEXT VAR_TELEPHONE");
                    std::cout << q2c(m) << std::endl;
                    QByteArray ba = m.toLocal8Bit();
                    const char *ex = ba.data();
                    system(ex);

                    QThread::sleep(10);
                    std::cout << "10" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Une erreur s'est produite. :(" << std::endl
                      << q2c(query.lastError().text()) << std::endl;
        }

        // SMSToSkype synchro
        std::cout << "Bip" << std::endl;
        QThread::sleep(10);
        std::cout << "10 total" << std::endl;
        QThread::sleep(10);
        std::cout << "20 total" << std::endl;

        QString sends = QString("./send.sh ");
        sends.append(QString::number(n));
        QByteArray sendy = sends.toLocal8Bit();
        const char *send = sendy.data();

        std::cout << send << std::endl;

        n = system(send);
        n = n / 256;

        /*int ntmp = n;

        do
        {
            QString sends = QString("./send.sh ");
            sends.append(QString::number(n));
            QByteArray sendy = sends.toLocal8Bit();
            const char *send = sendy.data();

            n = system(send);

            QString echos = QString("echo DEBUG_");
            echos.append(QString::number(n));
            QByteArray echoy = echos.toLocal8Bit();
            const char *echo = echoy.data();
            std::cout << echo << std::endl;
            QThread::sleep(5);
            //r = false;
        } while (n != ntmp);*/
    }

    return a.exec();
}
