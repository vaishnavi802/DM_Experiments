import cv2
import numpy as np
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA

def enhance_images_with_clahe(image_paths, output_paths, target_shape):
    enhanced_images = []
    clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
    
    for i, image_path in enumerate(image_paths):
        input_image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
        enhanced_image = clahe.apply(input_image)
        enhanced_image_resized = cv2.resize(enhanced_image, target_shape)
        cv2.imwrite(output_paths[i], enhanced_image_resized)
        enhanced_images.append(enhanced_image_resized)
    
    return enhanced_images

image_paths = ["input.jpeg", "class1.jpeg", "class2.jpeg"]
output_image_paths = ["enhanced_image1.jpg", "enhanced_image2.jpg", "enhanced_image3.jpg"]

target_shape = (200, 200)  

enhanced_images = enhance_images_with_clahe(image_paths, output_image_paths, target_shape)

X = np.array([img.ravel() for img in enhanced_images])

n_components = 2 
pca = PCA(n_components=n_components)
X_pca = pca.fit_transform(X)

n_clusters = 2  
kmeans = KMeans(n_clusters=n_clusters, random_state=42)
labels = kmeans.fit_predict(X_pca)

image_clusters = [[] for _ in range(n_clusters)]
for i, label in enumerate(labels):
    image_clusters[label].append(image_paths[i])
    
for cluster_idx, image_paths in enumerate(image_clusters):
    print(f"Cluster {cluster_idx + 1}:")
    for path in image_paths:
        print(path)
