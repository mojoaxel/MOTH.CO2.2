#include "DatCsvResponse.h"

#include "ModuleCard.h"
#include "ModuleHttp.h"

DatCsvResponse::~DatCsvResponse() {
    if (_content) {
        _content.close();
    }
}

DatCsvResponse::DatCsvResponse(String path) : AsyncAbstractResponse() {

    ModuleCard::begin();

    firstFill = true;

    _code = 200;
    _path = path;
    _content.open(_path.c_str(), O_RDONLY);
    _contentLength = CSV_HEAD.length() + _content.size() * CSV_LINE_LENGTH / sizeof(values_all_t);
    _contentType = "text/csv";

    char nameBuf[16];
    _content.getName(nameBuf, 16);
    char dispositionBuffer[64];
    sprintf(dispositionBuffer, "attachment; filename=\"%s\"", nameBuf);
    addHeader("Content-Disposition", dispositionBuffer);

    lastModified = SensorTime::getDateTimeLastModString(_content);

    if (SensorTime::isPersistPath(path)) {
        uint8_t measurementsUntilUpdate = MEASUREMENT_BUFFER_SIZE - Values::values->nextMeasureIndex % MEASUREMENT_BUFFER_SIZE;
        char maxAgeBuf[16];
        sprintf(maxAgeBuf, "max-age=%s", String(measurementsUntilUpdate * SECONDS_PER___________MINUTE));
        addHeader("Cache-Control", maxAgeBuf);
    } else {
        addHeader("Cache-Control", "max-age=31536000");
    }
    addHeader("Last-Modified", lastModified);
}

bool DatCsvResponse::wasModifiedSince(String ifModifiedSince) {
    return ifModifiedSince != lastModified;
}

size_t DatCsvResponse::_fillBuffer(uint8_t *data, size_t maxLen) {
    if (firstFill) {
        for (uint8_t charIndex = 0; charIndex < CSV_HEAD.length(); charIndex++) {
            data[charIndex] = CSV_HEAD[charIndex];
        }
        firstFill = false;
        return CSV_HEAD.length();
    } else {
        uint8_t lineLimit = min(50U, maxLen / CSV_LINE_LENGTH);
        uint16_t offset;
        values_all_t datValue;
        for (uint8_t lineIndex = 0; lineIndex < lineLimit; lineIndex++) {
            offset = lineIndex * CSV_LINE_LENGTH;
            if (_content.available() >= sizeof(values_all_t)) {
                _content.read((byte *)&datValue, sizeof(datValue));
                ModuleHttp::fillBufferWithCsv(&datValue, data, offset);
            }
        }
        return CSV_LINE_LENGTH * lineLimit;
    }
}
