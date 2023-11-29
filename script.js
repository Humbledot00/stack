// Set up the scene, camera, and renderer
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Create a box geometry
const geometry = new THREE.BoxGeometry();
// Create a material with a basic color
const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
// Combine the geometry and material to create a mesh (the 3D object)
const box = new THREE.Mesh(geometry, material);
// Add the box to the scene
scene.add(box);

// Set the camera position
camera.position.z = 5;

// Create an animation loop
const animate = function () {
  requestAnimationFrame(animate);

  // Render the scene with the camera
  renderer.render(scene, camera);
};

// Function to update rotation based on received data
function updateRotation(data) {
  // Assuming data is a string with values "0" or "10"
  // Split the string by commas
let dataArray = data.split(',');

// Assign each part to a variable
let variable_x = parseFloat(dataArray[0]);
let variable_y = parseFloat(dataArray[1]);
let variable_z = parseFloat(dataArray[2]);

  // Update the rotation of the box
  box.rotation.x = variable_x;
  box.rotation.y = variable_y;
  box.rotation.z = variable_z;

}

// Start the animation loop
animate();

// WebSocket connection to receive real-time updates
const socket = new WebSocket('ws://localhost:3000');
socket.addEventListener('open', function (event) {
  console.log('WebSocket connected');
});

socket.addEventListener('message', function (event) {
  const receivedData = event.data;
  console.log(receivedData);

  // Update rotation based on received data
  updateRotation(receivedData);
});
