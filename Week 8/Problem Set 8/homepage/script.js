const products = [
    {
        image: "images/upper-body.jpg",
        name: "Upper Body in the Gym",
        description: "Exercises to work the upper body",
        category: "upperbody"
    },
    {
        image: "images/lower-body.jpg",
        name: "Lower Body in the Gym",
        description: "Exercises to work the lower body",
        category: "lowerbody"
    },
    {
        image: "images/stretch.jpg",
        name: "Stretching at Home",
        description: "Exercises to stretch your body at home",
        category: "yoga-stretch"
    },
    {
        image: "images/yoga.jpg",
        name: "Yoga at Home",
        description: "Yoga class to do at home",
        category: "yoga-stretch"
    },
    {
        image: "images/cycling.jpg",
        name: "Cycling",
        description: "Cycling class to do at the gym or at home",
        category: "cycling"
    },
    {
        image: "images/outdoor-running.jpg",
        name: "Running - Outdoor",
        description: "Get tips to practice running in the outdoor",
        category: "running"
    },
    {
        image: "images/running-gym.jpg",
        name: "Running - Gym",
        description: "Get tips to practice running in the gym",
        category: "running"
    }
];

const productCardsContainer = document.querySelector(".product-cards");
const categoryButtons = document.querySelectorAll(".category-btn");

document.addEventListener('DOMContentLoaded',async function () {
async function fetchNavBar() {
    const response = await fetch('nav-bar.html');
    const navbarHTML = await response.text();
    document.querySelector('#navMenu').innerHTML = navbarHTML;

    addActiveClassToCurrentPageLink();
}

function addActiveClassToCurrentPageLink() {
    const currentLocation = window.location.href;
    const navLinks = document.querySelectorAll('.nav-link');

    for (const navLink of navLinks) {
        if (navLink.href === currentLocation) {
            navLink.classList.add('active');
            break;
        }
    }
}

function generateProductCards(category) {
    productCardsContainer.innerHTML = "";

    const filteredProducts = category === "all" ? products : products.filter(product => product.category === category);

    filteredProducts.forEach(product => {
        const productCard = document.createElement("div");
        productCard.classList.add("product-card");

        const image = document.createElement("img");
        image.src = product.image;
        image.alt = product.name;

        const name = document.createElement("h3");
        name.textContent = product.name;

        const description = document.createElement("p");
        description.textContent = product.description;

        productCard.appendChild(image);
        productCard.appendChild(name);
        productCard.appendChild(description);

        productCardsContainer.appendChild(productCard);
    });
}

function handleCategoryButtonClick(button) {
    categoryButtons.forEach(btn => btn.classList.remove("active"));
    button.classList.add("active");

    const selectedCategory = button.dataset.category;
    generateProductCards(selectedCategory);
}

function setupCategoryButtonListeners() {
    categoryButtons.forEach(button => {
        button.addEventListener("click", () => handleCategoryButtonClick(button));
    });
}

    await fetchNavBar();
    generateProductCards("all");
    setupCategoryButtonListeners();
});