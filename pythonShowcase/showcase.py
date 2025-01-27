import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_data(filename):
    with open(filename, 'r') as file:
        data = file.readlines()
    return [np.array(list(map(float, line.strip().split()))) for line in data]

def create_horizontal_plane(y_value, x_range, z_range):
    xx, zz = np.meshgrid(x_range, z_range)
    yy = np.full_like(xx, y_value)  
    return xx, yy, zz

def create_plane_from_points(three_points):
    point1, point2, point3 = three_points
    v1 = point2 - point1
    v2 = point3 - point1
    normal = np.cross(v1, v2)
    d = -np.dot(normal, point1)
    
    x_min, x_max = min(point1[0], point2[0], point3[0]), max(point1[0], point2[0], point3[0])
    z_min, z_max = min(point1[2], point2[2], point3[2]), max(point1[2], point2[2], point3[2])
    
    x_range = np.linspace(x_min - 1, x_max + 1, 20)
    z_range = np.linspace(z_min - 1, z_max + 1, 20)
    
    xx, zz = np.meshgrid(x_range, z_range)
    yy = (-normal[0] * xx - normal[2] * zz - d) / normal[1]  
    return xx, yy, zz

plane_points = read_data('/path/to/planes.txt')  
points = read_data('/path/to/points.txt')       

plane1_points = plane_points[:3]
plane2_points = plane_points[3:6]

y_value = -0.33  
x_range = np.linspace(-2, 2, 20)
z_range = np.linspace(-2, 2, 20)
xx1, yy1, zz1 = create_horizontal_plane(y_value, x_range, z_range)

try:
    xx2, yy2, zz2 = create_plane_from_points(plane2_points)
except ValueError as e:
    print(f"Ошибка при создании плоскости: {e}")
    exit()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(xx1, yy1, zz1, alpha=0.5, color='blue', label='Plane 1 (y = -0.33)')
ax.plot_surface(xx2, yy2, zz2, alpha=0.5, color='green', label='Plane 2')

points_array = np.array(points)
ax.scatter(points_array[:, 0], points_array[:, 1], points_array[:, 2], color='red', label='Points', s=10)  # Уменьшаем размер точек

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

ax.set_xlim([-2, 2])
ax.set_ylim([-2, 2])
ax.set_zlim([-2, 2])

ax.legend()

ax.view_init(elev=60, azim=160)  

plt.savefig('output.png', dpi=300, bbox_inches='tight')