import cv2

image = cv2.imread('text.png', cv2.IMREAD_GRAYSCALE)

count = 0
for line in image:
    for el in line:
        if el != 255:
            count += 1

f = open('particlepositions2.out', 'r')
particles = []
for line in f:
    #print(line)
    particle = {}
    data = line.strip().split(' ')
    particle['x'], particle['y'] = map(float, data[0:2])
    particle['id'] = int(data[2])
    particles.append(particle)
f.close()

keep = []

for particle in particles:
    x, y = [int(particle['x']), int(particle['y'])]
    if x in range(0, 1000) and y in range(0, 1000):
        if image[y][x] < 255 and particle['id'] not in keep:
            keep.append(particle['id'])

print(keep)

#print(" ".join(map(str, image)))
