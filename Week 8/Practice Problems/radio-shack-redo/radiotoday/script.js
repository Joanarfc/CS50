// Define the navigation links
const navLinksData = [
  { text: 'Store Locator', href: '#' },
  { text: "Steve's Workbench", href: '#' },
  { text: 'RadioShack Services', href: '#' },
  { text: 'Electronic Repair', href: '#' },
  { text: 'About RadioShack', href: '#' },
  { text: 'Product Support', href: '#' },
];

// Define the cards information
const cards = [
  {
    image: "rock-and-roll-on-tour.jpg",
    title: "Rock and Roll OnTour",
    description: "Rock and Roll Hall of Fame and Museum OnTour Exhibit.",
    price: "€30"
  },
  {
    image: "united-crime.jpg",
    title: "United Against Crime",
    description: "Free videos, brochures and a quarterly teleconference focusing on Crime Prevention.",
    price: "€30"
  },
  {
    image: "home-security.jpg",
    title: "Home Security",
    description: "How to protect your family and property from burglars and intruders.",
    price: "€30"
  },
  {
    image: "tv-fm-reception.jpg",
    title: "TV/FM Reception",
    description: "Answers to your Direct-to-Home, Outdoor and Indoor Reception questions.",
    price: "€30"
  }
];

// Define the footer links array
  const companyInfoLinks = [
    { label: "About", url: "#" },
    { label: "Store Locator", url: "#" },
    { label: "Services", url: "#" },
    { label: "Contacts", url: "#" }
  ];
  const customerSupportLinks = [
    { label: "Terms & Conditions", url: "#" },
    { label: "Privacy Policy", url: "#" },
    { label: "Product Support", url: "#" },
    { label: "Shipping Information", url: "#" }
  ];
  const currentYear = new Date().getFullYear();
  const companyName = "Tandy Corporation";

// Function to generate the navigation links dynamically
function generateNavLinks() {
  const navLinksContainer = document.getElementById('navLinks');

  navLinksData.forEach((link) => {
    const listItem = document.createElement('li');
    listItem.classList.add('nav-item');

    const anchor = document.createElement('a');
    anchor.classList.add('nav-link');
    anchor.href = link.href;
    anchor.textContent = link.text;

    listItem.appendChild(anchor);
    navLinksContainer.appendChild(listItem);
  });
}

// Function to generate the product cards dynamically
function generateProductCards() {
  const cardRow = document.getElementById("cardRow");
  cards.forEach(card => {
    const col = document.createElement("div");
    col.classList.add("col-md-3");

    const cardHtml = `
          <div class="card" style="width: 18rem;">
            <div class="card card-product-grid">
              <img src="${card.image}" class="card-img-top" alt="${card.title}">
              <a href="#"></a>
              <div class="card-body">
                <h5 class="card-title">${card.title}</h5>
                <p class="card-text">${card.description}</p>
                <div class="card-footer price mt-1">
                  <h3>${card.price}</h3>
                </div>
              </div>
            </div>
          </div>
        `;

    col.innerHTML = cardHtml;
    cardRow.appendChild(col);
  });
}


// Function to generate the footer links dynamically
function generateFooter() {
  // Get the container elements
  const companyInfoList = document.getElementById("company-info");
  const customerSupportList = document.getElementById("customer-support");
  const footerText = document.getElementById("footer-text");

  // Generate the company information links
  companyInfoLinks.forEach(link => {
    const listItem = document.createElement("li");
    const anchor = document.createElement("a");
    anchor.href = link.url;
    anchor.className = "nav-link p-0 text-body-secondary";
    anchor.textContent = link.label;
    listItem.appendChild(anchor);
    companyInfoList.appendChild(listItem);
  });

  // Generate the customer support links
  customerSupportLinks.forEach(link => {
    const listItem = document.createElement("li");
    const anchor = document.createElement("a");
    anchor.href = link.url;
    anchor.className = "nav-link p-0 text-body-secondary";
    anchor.textContent = link.label;
    listItem.appendChild(anchor);
    customerSupportList.appendChild(listItem);
  });

  // Set the footer text
  footerText.textContent = `Copyright © ${currentYear} ${companyName}, All rights reserved.`;
}


document.addEventListener("DOMContentLoaded", function () {
  generateNavLinks(); // Function call to generate the navigation links
  generateProductCards(); // Function call to generate the product cards
  generateFooter(); // Function call to generate the footer links
});