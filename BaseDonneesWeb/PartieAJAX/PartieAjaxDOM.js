 //--------------------------------------------------------------------------------------------------------------
 // Fonction permettant d'initialiser l'application en cachant les lignes inutiles 
 // à l'ouverture du tableau. 
function init()
{
	// on cache les différents bouton qui doivent sortir une fois que nous avons appuyé sur
	// différents boutons. 
	afficher_cacher("TableauIndice2");
	afficher_cacher("Button3");    
}

//--------------------------------------------------------------------------------------------------------------
// Fonction permettant de modifier la couleur en arriére plan et de modifier la couleur du bouton
// La méthode texte le contexte actuel de la page et change de couleurs en fonction de celle actuellement utilisé. 

function ChangerCouleur() {

  	var body = document.getElementById("body");
  	var bouton = document.getElementById("myButton1");
  	// Nous testons la configuration actuel de la fenetre. 

  	if(bouton.style.color == "white")
	{
      body.style.background = "white"; /* Le fond de la page sera noir */
      bouton.style.color = "black";
	}
	else 
	{
      body.style.background = "blue";
      bouton.style.color = "white";
	}
}

//--------------------------------------------------------------------------------------------------------------
//charge le fichier XML se trouvant à l'URL relative donné dans le paramètre le retourne
function getHttpXML(xmlDocumentUrl) { 
  
  var httpAjax;

  httpAjax = window.XMLHttpRequest ?
    new XMLHttpRequest() :
    new ActiveXObject('Microsoft.XMLHTTP');
  
  if (httpAjax.overrideMimeType) {
    httpAjax.overrideMimeType('text/xml');
  }
  
  //chargement du fichier XML à l'aide de XMLHttpRequest synchrone (le 3° paramètre est défini à false)
  httpAjax.open('GET', xmlDocumentUrl, false);
  httpAjax.send();
  
  return httpAjax.responseXML;
}

//--------------------------------------------------------------------------------------------------------------
// fonction permettant de cacher un element du DOM référencé par son id.
function afficher_cacher(id)
{
    if(document.getElementById(id).style.visibility=="hidden"){
        document.getElementById(id).style.visibility="visible";
    }
    else{
        document.getElementById(id).style.visibility="hidden";
    }
    return true;
} 

//--------------------------------------------------------------------------------------------------------------
function recupererPremierElementEnfant(n) {
  x = n.firstChild;
  while ( x.nodeType != 1 ) { // Test if x is an element node (and not a text node or other)
    x = x.nextSibling;
  }
  
  return x;
}

//--------------------------------------------------------------------------------------------------------------
function RemplacerContenu(xmlDocumentUrl, xslDocumentUrl, newElementName) {
  
  var xsltProcessor = new XSLTProcessor();
  
  // Chargement du fichier XSL à l'aide de XMLHttpRequest synchrone (le 3° paramètre est défini à false)
  var xslDocument = getHttpXML(xslDocumentUrl);
  
  // Importation du .xsl
  xsltProcessor.importStylesheet(xslDocument);
  
  // Chargement du fichier XML à l'aide de XMLHttpRequest synchrone (le 3° paramètre est défini à false)
  var xmlDocument =  getHttpXML(xmlDocumentUrl);

  // Création du document XML transformé par le XSL
  var newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);

  // Recherche du parent (dont l'id est "remplacerCeci") de l'élément à remplacer dans le document HTML courant
  var elementHtmlParent = window.document.getElementById("remplacerCeci");

  // Premier élément fils du parent
  var elementHtmlARemplacer = recupererPremierElementEnfant(elementHtmlParent);

  // Premier élément "elementName" du nouveau document (par exemple, "ul", "table"...)
  var elementAInserer = newXmlDocument.getElementsByTagName(newElementName)[0];

  // mettons a jour les information demandé dans l'énoncé
  var temp = elementAInserer.getElementsByTagName('div')[0].getElementsByTagName('h4')[0].innerHTML;
  elementAInserer.getElementsByTagName('div')[0].setAttribute("id",temp)
  var test = elementAInserer.getElementsByTagName('div')[0].getElementsByTagName('div')[2].innerHTML;
  elementAInserer.getElementsByTagName('div')[0].getElementsByTagName('div')[2].setAttribute('href',test);
  
  // Remplacement de l'élément
  elementHtmlParent.replaceChild(elementAInserer,elementHtmlARemplacer);

}

//--------------------------------------------------------------------------------------------------------------
// Permet de recupere les information sur les éléments contenant le mot "Workaholics" 
// La méthode permet de la même maniere de rendre visible la ligne numéro 3. 
function Question2 (xmlDocumentUrl, xslDocumentUrl, newElementName){

	// on affiche le bouton et la ligne du tableau contenant le bouton 3
  if(document.getElementById("TableauIndice2").style.visibility=="hidden"){
	 afficher_cacher("TableauIndice2");
	 afficher_cacher("Button3"); 
  }
	     
	// on affiche les resultats voulues.
	RemplacerContenu(xmlDocumentUrl, xslDocumentUrl, newElementName)

}

//--------------------------------------------------------------------------------------------------------------
// Permet de recupere les information sur les éléments contenant le mot "Workaholics" 
// La méthode permet de la même maniere de rendre visible la ligne numéro 3. 
  function getHttpJSON(jsonDocumentUrl) {

        var httpAjax;

        httpAjax = window.XMLHttpRequest ?
                    new XMLHttpRequest() :
                    new ActiveXObject('Microsoft.XMLHTTP');

            if (httpAjax.overrideMimeType) {
                httpAjax.overrideMimeType('application/json');
            }

            // chargement du fichier JSON à l'aide de XMLHttpRequest synchrone (le 3° paramètre est défini à false)
            httpAjax.open('GET', jsonDocumentUrl, false);
            httpAjax.send();

            var responseData = eval("(" + httpAjax.responseText + ")");

            return responseData;
        } 

//--------------------------------------------------------------------------------------------------------------
//Permet d'ajouter un element à la liste detaillant notre évenemenemt. 
function add_li(idelementHtmlARemplacer,titre) {

    var temp = window.document.getElementById(idelementHtmlARemplacer);
    var elementHtmlARemplacer = recupererPremierElementEnfant(temp)
    var ilist = recupererPremierElementEnfant(elementHtmlARemplacer) // recupérationd de l'enfant <li>

    var url = "http://www.omdbapi.com/?t="+ titre +"&y=&plot=short&r=json"
    
    // nous récuperoins le fichier Json sur le site distant.
    var response = getHttpJSON(url); 

    var presenceLongueur = ilist.getElementsByTagName("a").length;
    var refElement = window.document.getElementById(titre);

    console.log(response);
    console.log(refElement);
    // Nous verifions que le noeaud n'est pas deja présent dans le DOM. 
    if (presenceLongueur === 1)
    {
      // création du noeaud a.
      var aElement = document.createElement("a");
      aElement.setAttribute("class", "pull-left thumbnail-size");
      //aElement.setAttribute("href", response.URLEpisode12);

      // création du noeud img
      var imgElement = document.createElement("img")
      imgElement.setAttribute("class", "media-object img-thumbnail responsive");
      imgElement.setAttribute("src", response.Poster);
   
      // On attache les différents noeuds.
      aElement.appendChild(imgElement);
      ilist.insertBefore(aElement, refElement) 

    }
}

//--------------------------------------------------------------------------------------------------------------
// Récupere les informations sur l'épisode. 
function ajaxDetailsEpisode12Workaholics(titre, idElementARemplacer) {

            var elementHtmlParent = window.document.getElementById(idElementARemplacer);

            // <ul>
            var temp = recupererPremierElementEnfant(elementHtmlParent);

            // <li>
            var episode = recupererPremierElementEnfant(temp);
            
            var presenceLongueur = episode.getElementsByTagName("div").length;

            // nous vérifie que l'ajout est unique. 
            if (presenceLongueur === 5)
            { 
              // Utilisation de l'API des films pour récuperer les données nécessaire au TP.
              var url = "http://www.omdbapi.com/?t="+ titre +"&y=&plot=short&r=json"
              // nous récuperoins le fichier Json sur le site distant.
              var response = getHttpJSON(url);       

              // Création de l'élément <div> correspondant aux caractéritiques du programme
              var moreInfos = document.createElement("div");
              episode.appendChild(moreInfos);
              
              // Création des labels
              var yearLabel = document.createElement("span");
              yearLabel.setAttribute("class", "label label-default");
              yearLabel.innerHTML = response.Year;
              var ratedLabel = document.createElement("span");
              ratedLabel.setAttribute("class", "label label-default");
              ratedLabel.innerHTML = response.Rated;
              var releasedLabel = document.createElement("span");
              releasedLabel.setAttribute("class", "label label-default");
              releasedLabel.innerHTML = response.Released;
              var runtimeLabel = document.createElement("span");
              runtimeLabel.setAttribute("class", "label label-default");
              runtimeLabel.innerHTML = response.Runtime;
              var genreLabel = document.createElement("span");
              genreLabel.setAttribute("class", "label label-default");
              genreLabel.innerHTML = response.Genre;
              var languageLabel = document.createElement("span");
              languageLabel.setAttribute("class", "label label-default");
              languageLabel.innerHTML = response.Language;
              var countryLabel = document.createElement("span");
              countryLabel.setAttribute("class", "label label-default");
              countryLabel.innerHTML = response.Country;
              var imdbRatingLabel = document.createElement("span");
              imdbRatingLabel.setAttribute("class", "label label-default");
              imdbRatingLabel.innerHTML = response.imdbRating;
              var imdbVotesLabel = document.createElement("span");
              imdbVotesLabel.setAttribute("class", "label label-default");
              imdbVotesLabel.innerHTML = response.imdbVotes;  
            
              moreInfos.appendChild(yearLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(ratedLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(releasedLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(runtimeLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(genreLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(languageLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(countryLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(imdbRatingLabel);
              moreInfos.appendChild(document.createTextNode (" "));
              moreInfos.appendChild(imdbVotesLabel);
            }
        }

//--------------------------------------------------------------------------------------------------------------
// Permet de recupere les information sur les éléments contenant le mot "Workaholics" 
// La méthode permet de la même maniere de rendre visible la ligne numéro 3. 
function Question3 (remplacerCeci){

	// on affiche le bouton et la ligne du tableau contenant le bouton 4
  if(document.getElementById("TableauIndice3").style.visibility=="hidden"){
   afficher_cacher("TableauIndice3");
  }

  // Nous ajoutons l'image que nous devons afficher. 
  add_li(remplacerCeci,"Workaholics");

  // Nous ajoutons les informations nécesasaire au programme.
  ajaxDetailsEpisode12Workaholics("Workaholics", remplacerCeci);
	     
}

function RemplacerContenuTousSeries(xmlDocumentUrl, xslDocumentUrl, newElementName) 
{
  
  var xsltProcessor = new XSLTProcessor();
  
  // Chargement du fichier XSL à l'aide de XMLHttpRequest synchrone (le 3° paramètre est défini à false)
  var xslDocument = getHttpXML(xslDocumentUrl);
  
  // Importation du .xsl
  xsltProcessor.importStylesheet(xslDocument);
  
  // Chargement du fichier XML à l'aide de XMLHttpRequest synchrone (le 3° paramètre est défini à false)
  var xmlDocument =  getHttpXML(xmlDocumentUrl);

  // Création du document XML transformé par le XSL
  var newXmlDocument = xsltProcessor.transformToDocument(xmlDocument);

  // Recherche du parent (dont l'id est "remplacerCeci") de l'élément à remplacer dans le document HTML courant
  var elementHtmlParent = window.document.getElementById("remplacerCeci");

  // Premier élément fils du parent
  var elementHtmlARemplacer = recupererPremierElementEnfant(elementHtmlParent);

  // création du tableau contenant les evenement.
  var elementAInserer = document.createElement("table");
  elementAInserer.setAttribute('border', 1); 
  elementAInserer.setAttribute('id',"TableauInformations");

  var elementbody = document.createElement("tbody");
  elementAInserer.appendChild(elementbody);

  var longueur = newXmlDocument.getElementsByTagName(newElementName).length;
  var elementtr; 
  var pas;

  for (pas = 0; pas < longueur; pas ++)
  {
    // creation <tr>
    if (pas % 2 == 0)
    {
      elementr = document.createElement("tr");
      elementbody.appendChild(elementr);
    }

    // création <td>
    var elementd = document.createElement("td");
    elementr.appendChild(elementd);

    // Premier élément "elementName" du nouveau document (par exemple, "ul", "table"...)
    var elementRecuperer = newXmlDocument.getElementsByTagName(newElementName)[0];
	//console.log("Dans la boucle" + newXmlDocument.getElementsByTagName(newElementName)[pas]);

    if(elementRecuperer)
    {
      // mettons a jour les information demandé dans l'énoncé
	  var url = elementRecuperer.getElementsByTagName('div')[0].getElementsByTagName('div')[2].innerHTML;
      elementRecuperer.getElementsByTagName('div')[0].setAttribute("id",url);
      elementRecuperer.getElementsByTagName('div')[0].getElementsByTagName('div')[2].setAttribute('href',url);
      
      elementd.appendChild(elementRecuperer);
    }
    if (pas % 2 == 1 || pas == longueur - 1)
    {
        elementbody.appendChild(elementr);
    }
  }

  // Remplacement de l'élément
  elementHtmlParent.replaceChild(elementAInserer,elementHtmlARemplacer);

}

//--------------------------------------------------------------------------------------------------------------
// Permet de recupere les information sur les éléments contenant le mot "Workaholics" 
// La méthode permet de la même maniere de rendre visible la ligne numéro 3. 
function Question4(xmlDocumentUrl, xslDocumentUrl, newElementName){

	// on affiche le bouton et la ligne du tableau contenant le bouton 4
  if(document.getElementById("TableauIndice4").style.visibility=="hidden"){
   afficher_cacher("TableauIndice4");
  }
	     
  RemplacerContenuTousSeries(xmlDocumentUrl, xslDocumentUrl, newElementName);
  
}

//--------------------------------------------------------------------------------------------------------------
// 
function ModificationAffichage (fichierJSON,idElementARemplacer)
{
  var temp = window.document.getElementById(idElementARemplacer);
  if (temp)
  {
    var elementTab = temp.getElementsByTagName('ul');

    var pas
    for(pas = 0; pas < elementTab.length; pas++ )
    {
      // ici on se situe pour chaque élement qui compose le tableau, il faut chercher Json Api et modifier la forme
      // de l'affichage en utilisant les autres fonctions.

      var titre = elementTab[pas].getElementsByTagName('div')[0].getElementsByTagName('h4')[0].innerHTML;
	  var urlId = elementTab[pas].getElementsByTagName('div')[0].getElementsByTagName('div')[2].innerHTML;


      var ilist = recupererPremierElementEnfant(elementTab[pas]) // recupération de l'enfant <li>

      // Utilisation de l'API des films pour récuperer les données nécessaire au TP.
      var url = "http://www.omdbapi.com/?t="+ titre +"&y=&plot=short&r=json"
      // nous récuperoins le fichier Json sur le site distant.
      var response = getHttpJSON(url);   

      var presenceLongueur = ilist.getElementsByTagName("a").length;
      var refElement = window.document.getElementById(urlId);

      console.log(presenceLongueur);
      console.log(refElement);

      // Nous verifions que le noeaud n'est pas deja présent dans le DOM. 
      if (presenceLongueur === 1)
      {
        //----------------------------------------------------------------------------------------------------------------------------------------
        // Mise à jour de la photo
        var aElement = document.createElement("a");
        aElement.setAttribute("class", "pull-left thumbnail-size");
        aElement.setAttribute("href", response.URLEpisode12);

        // création du noeud img
        var imgElement = document.createElement("img")
        imgElement.setAttribute("class", "media-object img-thumbnail responsive");
        imgElement.setAttribute("src", response.Poster);
     
        // On attache les différents noeuds.
        aElement.appendChild(imgElement);
        ilist.insertBefore(aElement, refElement)

        //----------------------------------------------------------------------------------------------------------------------------------------       

        // Création de l'élément <div> correspondant aux caractéritiques du programme
        var moreInfos = document.createElement("div");
        elementTab[pas].appendChild(moreInfos);
        
        // Création des labels
        var yearLabel = document.createElement("span");
        yearLabel.setAttribute("class", "label label-default");
        yearLabel.innerHTML = response.Year;
        var ratedLabel = document.createElement("span");
        ratedLabel.setAttribute("class", "label label-default");
        ratedLabel.innerHTML = response.Rated;
        var releasedLabel = document.createElement("span");
        releasedLabel.setAttribute("class", "label label-default");
        releasedLabel.innerHTML = response.Released;
        var runtimeLabel = document.createElement("span");
        runtimeLabel.setAttribute("class", "label label-default");
        runtimeLabel.innerHTML = response.Runtime;
        var genreLabel = document.createElement("span");
        genreLabel.setAttribute("class", "label label-default");
        genreLabel.innerHTML = response.Genre;
        var languageLabel = document.createElement("span");
        languageLabel.setAttribute("class", "label label-default");
        languageLabel.innerHTML = response.Language;
        var countryLabel = document.createElement("span");
        countryLabel.setAttribute("class", "label label-default");
        countryLabel.innerHTML = response.Country;
        var imdbRatingLabel = document.createElement("span");
        imdbRatingLabel.setAttribute("class", "label label-default");
        imdbRatingLabel.innerHTML = response.imdbRating;
        var imdbVotesLabel = document.createElement("span");
        imdbVotesLabel.setAttribute("class", "label label-default");
        imdbVotesLabel.innerHTML = response.imdbVotes;  
      
        moreInfos.appendChild(yearLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(ratedLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(releasedLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(runtimeLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(genreLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(languageLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(countryLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(imdbRatingLabel);
        moreInfos.appendChild(document.createTextNode (" "));
        moreInfos.appendChild(imdbVotesLabel);

      }
    }
  }
}

//--------------------------------------------------------------------------------------------------------------
// Permet de recupere les information sur les éléments contenant le mot "Workaholics" 
// La méthode permet de la même maniere de rendre visible la ligne numéro 3. 
function Question5(fichierJSON,idElementARemplacer){

	     ModificationAffichage (fichierJSON,idElementARemplacer)
}

