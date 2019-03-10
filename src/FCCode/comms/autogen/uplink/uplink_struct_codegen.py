import math
import csv

with open('uplink_fields.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    header = next(csv_reader)
    FIELDS = [dict(zip(header, map(str, row))) for row in csv_reader]

for field in FIELDS:
    field["size"] = int(field['size'])
total_size = sum([field["size"] for field in FIELDS])

TYPES = ["bool", "int", "state int", "float vector", "double vector", "quaternion","gps time"]

struct_file = "/** THIS IS AN AUTOGENERATED FILE **/\n"
struct_file += "#ifndef UPLINK_STRUCT_HPP_\n"
struct_file += "#define UPLINK_STRUCT_HPP_\n\n"
struct_file += "#include <GPSTime.hpp>\n"
struct_file += "#include <array>\n\n"
struct_file += "namespace Comms {\n"
struct_file += "  constexpr unsigned int UPLINK_SIZE_BITS = {0};\n".format(total_size)
struct_file += "  struct Uplink {\n"

for field in FIELDS:
    if   field["type"] == "state int":
        struct_file += "    unsigned int {0};\n".format(field["name"])
    elif field["type"] == "float vector":
        struct_file += "    std::array<float, 3> {0};\n".format(field["name"])
    elif field["type"] == "double vector":
        struct_file += "    std::array<double, 3> {0};\n".format(field["name"])
    elif field["type"] == "gps time":
        struct_file += "    gps_time_t {0};\n".format(field["name"])
    elif field["type"] == "quaternion":
        struct_file += "    std::array<float, 4> {0};\n".format(field["name"])
    elif field["type"] not in TYPES:
        print "Undefined type for field {0}".format(field["name"])
    else:
        struct_file += "    {0} {1};\n".format(field["type"], field["name"])

struct_file += "  };\n"
struct_file += "}\n"
struct_file += "#endif"

f = open("../../uplink_struct.hpp", "w")
f.write(struct_file)
f.close()