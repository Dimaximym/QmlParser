#include "mainwindow.h"

#include <QApplication>

//void checkChilds(QDomNode node)
//{
//    QDomNode childNode = node.firstChild();
//    QString output = "c():" + node.nodeName() +  "->";
//    while (!childNode.isNull())
//    {
//        if (childNode.nodeName() == "widget")
//        {
//            qDebug() << "\t" << output << childNode.nodeName() << "=" << childNode.attributes().namedItem("class").nodeValue();
//        }

//        if (childNode.hasChildNodes())
//            checkChilds(childNode);

//        childNode = childNode.nextSibling();
//    }
//}

//QString findTag(QDomNode node, QString name)
//{
////    QDomNode childNode = node.firstChild();
////    while (!childNode.isNull())
////    {
////        if (childNode.nodeName() == "")
////    }
//}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    /// Реализация через QXmlStreamReader(удалено)
//    QXmlStreamReader xml(&file);

//    while (!xml.atEnd() && !xml.hasError())
//    {
//        QXmlStreamReader::TokenType token = xml.readNext();
//        if (token == QXmlStreamReader::StartDocument)
//            continue;
//        if (token == QXmlStreamReader::StartElement)
//        {
//            if (xml.name() == "class")
//                continue;
//            if (xml.name() == "widget")

//        }
//    }

/// Реализация через regexp(удалено)
//    QRegExp rx;
//    rx.setPattern("class=\\\"(\\S+(?=\\\"))");

//    QString str;
//    QTextStream in(&file);
//    str = in.readAll();
//    //qDebug() << str;

//    int pos = 0;
//    while ((pos = rx.indexIn(str)) != -1)
//    {
//        qDebug() << "Find " << rx.cap(1);
//        str = str.right(str.size() - (pos + rx.cap(1).size()));
//    }

    return app.exec();
}
