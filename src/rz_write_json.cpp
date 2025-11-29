/**
 * @file rz_write_flatbuffers.cpp
 * @author ZHENG Robert (robert.hase-zheng.net)
 * @brief write image metadata into FlatBuffers format
 * @version 0.2.0
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025 ZHENG Robert
 *
 */

#include "includes/rz_write_json.hpp"

#include <QDir>
#include "includes/rz_config.hpp"
#include <chrono>
#include <format>

Rz_writeJson::Rz_writeJson(QObject *parent)
{
  Q_UNUSED(parent);
}

std::tuple<bool, std::string> Rz_writeJson::isTargetExist(const QFile &pathToTarget,
                                                          const QString &type)
{
    const QFileInfo fInfo(pathToTarget);

    msg = "";
    oknok = false;

    if (type.contains("dir")) {
        if (!pathToTarget.exists()) {
            qDebug() << "createDirectories(fInfo.absolutePath().toStdString(): "
                     << fInfo.absolutePath().toStdString();
            std::tie(oknok, msg) = createDirectories(fInfo.absoluteFilePath().toStdString());
        }
        if (fInfo.isDir() && fInfo.isWritable()) {
            return std::make_tuple(true,
                                   std::format("{}:{}:{}: Folder exists and is writeable.",
                                               __FILE__,
                                               __FUNCTION__,
                                               __LINE__));
        } else {
            return std::make_tuple(
                true,
                std::format("{}:{}:{}: Target is not a directory or not writeable.",
                            __FILE__,
                            __FUNCTION__,
                            __LINE__));
        }
    }
    if (!pathToTarget.exists()) {
        return std::make_tuple(false,
                               std::format("{}:{}:{}: Target doesn't exist.",
                                           __FILE__,
                                           __FUNCTION__,
                                           __LINE__));
    }
    if (type.contains("file") && fInfo.isFile() && fInfo.isWritable()) {
        return std::make_tuple(true,
                               std::format("{}:{}:{}: File exists and is writeable",
                                           __FILE__,
                                           __FUNCTION__,
                                           __LINE__));
    }
    return std::make_tuple(false, std::format("{}:{}", __FILE__, __FUNCTION__));
}

std::tuple<bool, std::string> Rz_writeJson::createDirectories(const std::filesystem::path &p)
{
    std::filesystem::path nested = p;

    try {
        if (std::filesystem::create_directories(nested)) {
            return std::make_tuple(true,
                                   std::format("{}:{}:{}: Nested directories created successfully",
                                               __FILE__,
                                               __FUNCTION__,
                                               __LINE__));

        } else {
            return std::make_tuple(false,
                                   std::format("{}:{}:{}: Failed to create nested directories",
                                               __FILE__,
                                               __FUNCTION__,
                                               __LINE__));
            // std::cout << ec.message() << '\n';
        }
    } catch (const std::exception &ex) {
        std::string msg = std::format("{}:{}:{}: Failed creating directories: ",
                                      __FILE__,
                                      __FUNCTION__,
                                      __LINE__);
        msg.append(ex.what());
        return std::make_tuple(false, msg);
    }
}

QString Rz_writeJson::getPluginNameShort()
{
  return PROJECT_NAME.c_str();
}

QString Rz_writeJson::getPluginNameLong()
{
  return PROG_LONGNAME.c_str();
}

QString Rz_writeJson::getPluginVersion()
{
  std::string ret = std::format("{}-v{}", PROJECT_NAME, PROJECT_VERSION);
  return ret.c_str();
}

QString Rz_writeJson::getPluginDescription()
{
  return PROJECT_DESCRIPTION.c_str();
}

int32_t Rz_writeJson::getPluginMajorVersion()
{
    return PROJECT_VERSION_MAJOR;
}

int32_t Rz_writeJson::getPluginMinorVersion()
{
    return PROJECT_VERSION_MINOR;
}

int32_t Rz_writeJson::getPluginPatchVersion()
{
    return PROJECT_VERSION_PATCH;
}

QString Rz_writeJson::getPluginHomepageUrl()
{
    return PROJECT_HOMEPAGE_URL.c_str();
}

QString Rz_writeJson::getPluginCopyright()
{
    const auto now = std::chrono::system_clock::now();
    std::string ret = std::format("Copyright {}-{:%Y} {}", PROG_CREATED, now, PROG_AUTHOR);
    return ret.c_str();
}

QString Rz_writeJson::getPluginTechInfo()
{
    std::string ret = std::format("{} {}", CMAKE_CXX_COMPILER, CMAKE_CXX_STANDARD);
    return ret.c_str();
}

std::tuple<bool, std::string> Rz_writeJson::parseFile(const QString &type)
{
  return std::make_tuple(true, std::format("{}:{}", __FILE__, __FUNCTION__));
}

/**
 * @brief Rz_writeJson::writeFile
 * @param type <path to flatbuffers folder>
 * @return <bool, msg string>
 */
std::tuple<bool, std::string> Rz_writeJson::writeFile(const QString &pathToBinDir)
{
    std::tie(oknok, msg) = isTargetExist(QFile(pathToBinDir), "dir");
    if (!oknok) {
        return std::make_tuple(false,
                               std::format("{}:{}:{}: {}", __FILE__, __FUNCTION__, __LINE__, msg));
    }

    QString binFile = pathToBinDir + "/" + imgStruct.fileBasename + ".json";

    QFile out(binFile);
    if (out.open(QIODevice::WriteOnly)) {
        out.write(reinterpret_cast<const char *>(buf.data()), buf.size());
        out.close();
        qDebug() << "FlatBuffer saved: " << binFile << "(" << buf.size() << " bytes)\n";
    } else {
        qDebug() << "Unable to write file " << out.errorString();
        return std::make_tuple(false,
                               std::format("{}:{}: Unable to write file {}.",
                                           __FILE__,
                                           __FUNCTION__,
                                           out.errorString().toStdString()));
    }
    return std::make_tuple(true,
                           std::format("{}:{}: {}", __FILE__, __FUNCTION__, binFile.toStdString()));
}

std::tuple<bool, std::string> Rz_writeJson::doRun(const QString &type)
{
    return std::make_tuple(true, std::format("{}:{}", __FILE__, __FUNCTION__));
}

std::tuple<bool, std::string> Rz_writeJson::doClose(const QString &type)
{
    return std::make_tuple(true, std::format("{}:{}", __FILE__, __FUNCTION__));
}

std::tuple<bool, std::string> Rz_writeJson::setQstring(const QString &string, const QString &type)
{
    if (type.contains("imgStruct")) {
        QFileInfo fileInfo(string);

        imgStruct.fileName = fileInfo.fileName();
        imgStruct.fileBasename = fileInfo.completeBaseName();
        imgStruct.fileSuffix = fileInfo.completeSuffix();
        imgStruct.fileAbolutePath = fileInfo.absolutePath();
        imgStruct.homePath = QDir::homePath();
        return std::make_tuple(true,
                               std::format("{}:{}:{}: imgStruct", __FILE__, __FUNCTION__, __LINE__));
    }

    return std::make_tuple(false, std::format("{}:{}: wrong paramater", __FILE__, __FUNCTION__));
}

QString Rz_writeJson::getQstring(const QString &type)
{
    return "";
}

std::tuple<bool, std::string> Rz_writeJson::setQList(const QList<QString> &stringList,
                                                     const QString &type)
{
    return std::make_tuple(true, std::format("{}:{}:{}", __FILE__, __FUNCTION__, __LINE__));
}

QList<QString> Rz_writeJson::getQList(const QString &type)
{
    QList<QString> list("blender");
    return list;
}

std::tuple<bool, std::string> Rz_writeJson::setQMap(const QMap<QString, QString> &setQmap,
                                                    const QString &type)
{
    return std::make_tuple(true, std::format("{}:{}:{}", __FILE__, __FUNCTION__, __LINE__));
}

QMap<QString, QString> Rz_writeJson::getQMap(const QString &type)
{
  return qMap;
}

std::tuple<bool, std::string> Rz_writeJson::setQHash(const QHash<QString, QString> &setQhash,
                                                     const QString &type)
{
  if (type.contains("PICTURE"))
  {
    pictureData = setQhash;
    return std::make_tuple(true, std::format("{}:{}: PICTURE", __FILE__, __FUNCTION__));
  }
  if (type.contains("EXIF"))
  {
    exifData = setQhash;
    return std::make_tuple(true, std::format("{}:{}: EXIF", __FILE__, __FUNCTION__));
  }
  if (type.contains("IPTC"))
  {
    iptcData = setQhash;
    return std::make_tuple(true, std::format("{}:{}: IPTC", __FILE__, __FUNCTION__));
  }
  if (type.contains("XMP"))
  {
    xmpData = setQhash;
    return std::make_tuple(true, std::format("{}:{}: XMP", __FILE__, __FUNCTION__));
  }

  return std::make_tuple(false,
                         std::format("{}:{}:{}: wrong parameter", __FILE__, __FUNCTION__, __LINE__));
}

QHash<QString, QString> Rz_writeJson::getQHash(const QString &type)
{
  return exifData;
}
