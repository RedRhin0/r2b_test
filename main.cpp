#include <iostream>
#include "geom3d.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " <path/to/points> <path/to/planes>" << '\n';
    return 1;
  }

  // planes reading
  std::vector<Point3D> planePoints = readPointsFromFile(argv[2]);
  if (planePoints.size() % 3 != 0)
  {
    std::cerr << "Error: Not enough points for plane." << '\n';
    return 1;
  }

  // mb not 2 in future. Read N planes, work only with [0,1]
  std::vector<Plane> planes(planePoints.size() / 3);

  if (planes.size() < 2)
  {
    std::cerr << "Error: Not enough planes." << '\n';
    return 1;
  }

  for (int i = 0; i < planePoints.size() / 3; ++i)
  {
    planes[i] = Plane(planePoints[i * 3], planePoints[i * 3 + 1], planePoints[i * 3 + 2]);
    // std::cout << "Plane " << i << ':' << planes[i] << '\n';
  }

  // points reading
  std::ifstream pointsFile(argv[1]);
  if (!pointsFile.is_open())
  {
    std::cerr << "Error: can not open the file: " << argv[1] << '\n';
    return 1;
  }

  // task :
  /*

    В качестве первого аргумента командной строки программа должна принимать
  имя исходного файла с точками (points.txt), а в качестве второго имя файла с
  координатами точек, которые задают плоскости (plains.txt). В файл <имя
  исходного файла>_good.txt программа должна сохранить все корректные
  точки, а в файл <имя исходного файла>_ wrong.txt все "ложные" точки.

 */
  // so ans is written to "point.txt_good.txt"? i don't think so
  std::string baseFileName = argv[1];
  // remove extension if exists
  size_t lastDot = baseFileName.find_last_of('.');
  if (lastDot != std::string::npos)
    baseFileName = baseFileName.substr(0, lastDot);

  std::string goodFileName = baseFileName + "_good.txt";
  std::string badFileName = baseFileName + "_bad.txt";
  std::ofstream goodFile(goodFileName);
  std::ofstream badFile(badFileName);

  if (!goodFile.is_open() || !badFile.is_open())
  {
    std::cerr << "Error: Failed to create files for writing results." << '\n';
    return 1;
  }

  // one by one, there is no reason to keep all points in memory
  Point3D origin(0, 0, 0);
  Point3D target;
  while (pointsFile >> target)
    if (isSameHalfSpace(planes[0], planes[1], target, origin))
      badFile << target << '\n';
    else
      goodFile << target << '\n';
  std::cout << "Results have been written to files " << goodFileName << " and " << badFileName << '\n';

  return 0;
};