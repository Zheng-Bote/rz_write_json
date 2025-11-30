/**
 * @file test_read.cpp
 * @author ZHENG Robert (robert.hase-zheng.net)
 * @brief testing (reading) the FlatBuffers bin file
 * @version 0.2.0
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025 ZHENG Robert
 *
 */

#include <QCoreApplication>

#include <cstdlib>
#include <exception>

#include <QHash>
#include <QString>
#include <QFile>
#include <QDebug>
#include <iostream>

/*
    if (auto ex = pic->exifdata())
    {
        exifData["file_name"] = fbStr(ex->file_name());
        exifData["gpstag"] = fbStr(ex->gpstag());
        exifData["imagedescription"] = fbStr(ex->imagedescription());
        exifData["gpslongituderef"] = fbStr(ex->gpslongituderef());
        exifData["gpsmapdatum"] = fbStr(ex->gpsmapdatum());
        exifData["imageuniqueid"] = fbStr(ex->imageuniqueid());
        exifData["imageid"] = fbStr(ex->imageid());
        exifData["gpslatituderef"] = fbStr(ex->gpslatituderef());
        exifData["usercomment"] = fbStr(ex->usercomment());
        exifData["gpsaltitude"] = fbStr(ex->gpsaltitude());
        exifData["documentname"] = fbStr(ex->documentname());
        exifData["gpstimestamp"] = fbStr(ex->gpstimestamp());
        exifData["copyright"] = fbStr(ex->copyright());
        exifData["gpsaltituderef"] = fbStr(ex->gpsaltituderef());
        exifData["gpsdatestamp"] = fbStr(ex->gpsdatestamp());
        exifData["gpslongitude"] = fbStr(ex->gpslongitude());
        exifData["gpslatitude"] = fbStr(ex->gpslatitude());
        exifData["datetimeoriginal"] = fbStr(ex->datetimeoriginal());
        exifData["securityclassification"] = fbStr(ex->securityclassification());
    }

    // -------------------------------
    // IPTC → QHash
    // -------------------------------
    if (auto iptc = pic->iptcdata())
    {
        iptcData["file_name"] = fbStr(iptc->file_name());
        iptcData["objectname"] = fbStr(iptc->objectname());
        iptcData["copyright"] = fbStr(iptc->copyright());
        iptcData["caption"] = fbStr(iptc->caption());
    }

    // -------------------------------
    // XMP → QHash
    // -------------------------------
    if (auto xmp = pic->xmpdata())
    {
        xmpData["file_name"] = fbStr(xmp->file_name());
        xmpData["copyrightowner"] = fbStr(xmp->copyrightowner());
        xmpData["documentname"] = fbStr(xmp->documentname());
        xmpData["zipcode"] = fbStr(xmp->zipcode());
        xmpData["language"] = fbStr(xmp->language());
        xmpData["countrycode"] = fbStr(xmp->countrycode());
        xmpData["localaddress"] = fbStr(xmp->localaddress());
        xmpData["sublocation"] = fbStr(xmp->sublocation());
        xmpData["category"] = fbStr(xmp->category());
        xmpData["provincestate"] = fbStr(xmp->provincestate());
        xmpData["city"] = fbStr(xmp->city());
        xmpData["imageid"] = fbStr(xmp->imageid());
        xmpData["keywords"] = fbStr(xmp->keywords());
        xmpData["countryname"] = fbStr(xmp->countryname());
        xmpData["streetname"] = fbStr(xmp->streetname());
        xmpData["rights"] = fbStr(xmp->rights());
        xmpData["description"] = fbStr(xmp->description());
        xmpData["title"] = fbStr(xmp->title());
        xmpData["subject"] = fbStr(xmp->subject());
        xmpData["securityclassification"] = fbStr(xmp->securityclassification());
    }

*/

int main()
{
    QHash<QString, QString> pictureHash;
    QHash<QString, QString> exifHash;
    QHash<QString, QString> iptcHash;
    QHash<QString, QString> xmpHash;
}
