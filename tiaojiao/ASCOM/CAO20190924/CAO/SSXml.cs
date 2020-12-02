using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data;
using System.Configuration;
//using System.Web;
using System.IO;
using System.Xml;

namespace CAO
{
    //**************************************
    //参考代码来源
    //https://www.jb51.net/article/87431.htm
    //作者：smartsmile2012   
    //**************************************
    public class SSXml : IDisposable
    {
        #region 静态函数
        //以下为单一功能的静态类    
        #region 读取XML到DataSet    
        /**//**************************************************     
        * 函数名称:GetXml(string XmlPath)     
        * 功能说明:读取XML到DataSet     
        * 参  数:XmlPath:xml文档路径     
        * 使用示列:         
        *     string xmlPath = Server.MapPath("/EBDnsConfig/DnsConfig.xml"); //获取xml路径     
        *     DataSet ds = XmlObject.GetXml(xmlPath); //读取xml到DataSet中     
        *************************************************/    
        /**//// <summary>    
        // 功能:读取XML到DataSet中    
        /// </summary>    
        /// <param name="XmlPath">xml路径</param>    
        /// <returns>DataSet</returns>    
        public static DataSet GetXml(string XmlPath)    
        {      
            DataSet ds = new DataSet();      
            ds.ReadXml(@XmlPath);      
            return ds; 
        }    
        #endregion    
        #region 读取xml文档并返回一个节点    
        /**//**************************************************     
        * 函数名称:ReadXmlReturnNode(string XmlPath,string Node)     
        * 功能说明:读取xml文档并返回一个节点:适用于一级节点     
        * 参  数: XmlPath:xml文档路径;Node 返回的节点名称     
        * 适应用Xml:<?xml version="1.0" encoding="utf-8" ?>     
        *      <root>     
        *        <dns1>ns1.everdns.com</dns1>    
        *      </root>     
        * 使用示列:         
        *     string xmlPath = Server.MapPath("/EBDnsConfig/DnsConfig.xml"); //获取xml路径     
        *     Response.Write(XmlObject.ReadXmlReturnNode(xmlPath, "mailmanager"));     
        ************************************************/    
        /**//// <summary>    
        /// 读取xml文档并返回一个节点:适用于一级节点    
        /// </summary>   
        /// <param name="XmlPath">xml路径</param>  
        /// <param name="NodeName">节点</param>    
        /// <returns></returns>    
        public static string ReadXmlReturnNode(string XmlPath, string Node)    
        {      
            XmlDocument docXml = new XmlDocument();      
            docXml.Load(@XmlPath);      
            XmlNodeList xn = docXml.GetElementsByTagName(Node);      
            return xn.Item(0).InnerText.ToString();    
        }    
        #endregion    
        #region 查找数据,返回一个DataSet    
        /**//**************************************************     
        * 函数名称:GetXmlData(string xmlPath, string XmlPathNode)     
        * 功能说明:查找数据,返回当前节点的所有下级节点,填充到一个DataSet中     
        * 参  数:xmlPath:xml文档路径;XmlPathNode:当前节点的路径     
        * 使用示列:          
        *     string xmlPath = Server.MapPath("/EBDomainConfig/DomainConfig.xml"); //获取xml路径    
        *     DataSet ds = new DataSet();  
        *     ds = XmlObject.GetXmlData(xmlPath, "root/items");//读取当前路径     
        *     this.GridView1.DataSource = ds;     
        *     this.GridView1.DataBind();     
        *     ds.Clear();  
        *     ds.Dispose();     
        * Xml示例:     
        *     <?xml version="1.0" encoding="utf-8" ?>     *      <root>     
        *       <items name="xinnet">     
        *       <url>http://www.fhxy.com/</url>     
        *        <port>80</port>     
        *   	</items>     
        *      </root>     ************************************************/    /**/
        /// <summary>    
        /// 查找数据,返回当前节点的所有下级节点,填充到一个DataSet中    
        ///</summary>    
        /// <param name="xmlPath">xml文档路径</param>    
        /// <param name="XmlPathNode">节点的路径:根节点/父节点/当前节点</param>    
        /// <returns></returns>    
        public static DataSet GetXmlData(string xmlPath, string XmlPathNode)    
        {      
            XmlDocument objXmlDoc = new XmlDocument();      
            objXmlDoc.Load(xmlPath);      
            DataSet ds = new DataSet();      
            StringReader read = new StringReader(objXmlDoc.SelectSingleNode(XmlPathNode).OuterXml);     
            ds.ReadXml(read);      
            return ds;    
        }    
        #endregion    
        #region 更新Xml节点内容    
        /**//**************************************************     
        * 函数名称:XmlNodeReplace(string xmlPath,string Node,string Content)     
        * 功能说明:更新Xml节点内容     
        * 参  数:xmlPath:xml文档路径;Node:当前节点的路径;Content:内容     
        * 使用示列:         
        *     string xmlPath = Server.MapPath("/EBDomainConfig/DomainConfig.xml"); //获取xml路径   
        *     XmlObject.XmlNodeReplace(xmlPath, "root/test", "56789"); //更新节点内容     
        ************************************************/    
        /**/
        /// <summary>    
        /// 更新Xml节点内容    
        /// </summary>    
        /// <param name="xmlPath">xml路径</param>    
        /// <param name="Node">要更换内容的节点:节点路径 根节点/父节点/当前节点</param>    
        /// <param name="Content">新的内容</param>    
        public static void XmlNodeReplace(string xmlPath, string Node, string Content)    
        {      
            XmlDocument objXmlDoc = new XmlDocument();      
            objXmlDoc.Load(xmlPath);      
            objXmlDoc.SelectSingleNode(Node).InnerText = Content;      
            objXmlDoc.Save(xmlPath);    
        }    
        #endregion    
        #region 删除XML节点和此节点下的子节点    
        /**//**************************************************     
        * 函数名称:XmlNodeDelete(string xmlPath,string Node)     
        * 功能说明:删除XML节点和此节点下的子节点     
        * 参  数:xmlPath:xml文档路径;Node:当前节点的路径;     
        * 使用示列:         
        *     string xmlPath = Server.MapPath("/EBDomainConfig/DomainConfig.xml"); //获取xml路径    
        *     XmlObject.XmlNodeDelete(xmlPath, "root/test"); //删除当前节点     
        ************************************************/    
        /**//// <summary>    
        /// 删除XML节点和此节点下的子节点    
        /// </summary>    
        /// <param name="xmlPath">xml文档路径</param>    
        /// <param name="Node">节点路径</param>    
        public static void XmlNodeDelete(string xmlPath, string Node)    
        {      
            XmlDocument objXmlDoc = new XmlDocument();      
            objXmlDoc.Load(xmlPath);      
            string mainNode = Node.Substring(0, Node.LastIndexOf("/"));      
            objXmlDoc.SelectSingleNode(mainNode).RemoveChild(objXmlDoc.SelectSingleNode(Node));      
            objXmlDoc.Save(xmlPath);    
        }    
        #endregion    
        #region 插入一个节点和此节点的子节点    
        /**//**************************************************     
        * 函数名称:XmlInsertNode(string xmlPath, string MailNode, string ChildNode, string Element,string Content)     
        * 功能说明:插入一个节点和此节点的字节点     
        * 参  数:xmlPath:xml文档路径;MailNode:当前节点的路径;ChildNode:新插入的节点;Element:插入节点的子节点;Content:子节点的内容     
        * 使用示列:      
        *     string xmlPath = Server.MapPath("/EBDomainConfig/DomainConfig.xml"); //获取xml路径    
        *     XmlObject.XmlInsertNode(xmlPath, "root/test","test1","test2","测试内容"); //插入一个节点和此节点的字节点     
        * 生成的XML格式为     
        *     <test>     
        *        <test1>     
        *          <test2>测试内容</test2>  
        *       </test1>     
        *      </test>     ************************************************/    
        /**//// <summary>    /// 插入一个节点和此节点的子节点    
        /// </summary>    
        /// <param name="xmlPath">xml路径</param>    
        /// <param name="MailNode">当前节点路径</param>    
        /// <param name="ChildNode">新插入节点</param>    
        /// <param name="Element">插入节点的子节点</param>    
        /// <param name="Content">子节点的内容,已经应用CDATA</param>    
        public static void XmlInsertNode(string xmlPath, string MailNode, string ChildNode, string Element, string Content)    
        {    
            XmlDocument objXmlDoc = new XmlDocument();      
            objXmlDoc.Load(xmlPath);      
            XmlNode objRootNode = objXmlDoc.SelectSingleNode(MailNode);      
            XmlElement objChildNode = objXmlDoc.CreateElement(ChildNode);      
            objRootNode.AppendChild(objChildNode);      
            XmlElement objElement = objXmlDoc.CreateElement(Element);      
            XmlCDataSection xcds = objXmlDoc.CreateCDataSection(Content);      
            objElement.AppendChild(xcds);      
            objChildNode.AppendChild(objElement);      
            objXmlDoc.Save(xmlPath);    
        }    
        #endregion    
        #region 插入一节点,带一属性    
        /**//**************************************************     
        * 函数名称:XmlInsertElement(string xmlPath, string MainNode, string Element, string Attrib, string AttribContent, string Content)     
        * 功能说明:插入一节点,带一属性     
        * 参数:xmlPath:xml文档路径;MailNode:当前节点的路径;Element:新插入的节点;Attrib:属性名称;AttribContent:属性值;Content:节点的内容     
        * 使用示列:         
        *     string xmlPath = Server.MapPath("/EBDomainConfig/DomainConfig.xml"); //获取xml路径    
        *     XmlObject.XmlInsertElement(xmlPath, "root/test", "test1", "Attrib", "属性值", "节点内容"); //插入一节点,带一属性     
        * 生成的XML格式为     
        *     <test>     
        *       <test1 Attrib="属性值">节点内容</test1>     
        *     </test>     
        ************************************************/    
        /**//// <summary>    /// 插入一节点,带一属性    
        /// </summary>    
        /// <param name="xmlPath">Xml文档路径</param>    
        /// <param name="MainNode">当前节点路径</param>    
        /// <param name="Element">新节点</param>    
        ///<param name="Attrib">属性名称</param>    
        /// <param name="AttribContent">属性值</param>    /// <param name="Content">新节点值</param>    
        public static void XmlInsertElement(string xmlPath, string MainNode, string Element, string Attrib, string AttribContent, string Content)    
        {      
            XmlDocument objXmlDoc = new XmlDocument();      
            objXmlDoc.Load(xmlPath); 
            XmlNode objNode = objXmlDoc.SelectSingleNode(MainNode);      
            XmlElement objElement = objXmlDoc.CreateElement(Element);      
            objElement.SetAttribute(Attrib, AttribContent);     
            objElement.InnerText = Content;      
            objNode.AppendChild(objElement);      
            objXmlDoc.Save(xmlPath);    
        }    
        #endregion    
        #region 插入一节点不带属性    
        /**//**************************************************     
        * 函数名称:XmlInsertElement(string xmlPath, string MainNode, string Element, string Content)     
        * 功能说明:插入一节点不带属性     
        * 参  数:xmlPath:xml文档路径;MailNode:当前节点的路径;Element:新插入的节点;Content:节点的内容     
        * 使用示列:          
        *     string xmlPath = Server.MapPath("/EBDomainConfig/DomainConfig.xml"); //获取xml路径   
        *     XmlObject.XmlInsertElement(xmlPath, "root/test", "text1", "节点内容"); //插入一节点不带属性
        * 生成的XML格式为     
        *     <test>     
        *         <text1>节点内容</text1>     
        *     </test>     ************************************************/    
        public static void XmlInsertElement(string xmlPath, string MainNode, string Element, string Content)    
        {      
            XmlDocument objXmlDoc = new XmlDocument();      
            objXmlDoc.Load(xmlPath);      
            XmlNode objNode = objXmlDoc.SelectSingleNode(MainNode);      
            XmlElement objElement = objXmlDoc.CreateElement(Element);      
            objElement.InnerText = Content;      
            objNode.AppendChild(objElement);      
            objXmlDoc.Save(xmlPath);    
        }    
        #endregion    //必须创建对象才能使用的类 
        #endregion

        #region 基本函数
        private bool _alreadyDispose = false;
        private XmlDocument xmlDoc;    
        //private XmlDocument xmlDoc = new XmlDocument();    
        //private XmlNode xmlNode;    
        //private XmlElement xmlElem;    
        #region 构造与释构    
        public SSXml()    
        {  
            xmlDoc= new XmlDocument();  
        }    
        ~SSXml()    
        {      
            Dispose();    
        }    
        protected virtual void Dispose(bool isDisposing)    
        {      
            if (_alreadyDispose) return;
            if (isDisposing)
            { }      
            _alreadyDispose = true;    
        }    
        #endregion   
        #region IDisposable 成员    
        public void Dispose()    
        {
            Dispose(true);      
            GC.SuppressFinalize(this);    
        }    
        #endregion    
        
        #region 创建一个只有声明和根节点的XML文档
        /**/
        /// <summary>    
        /// 创建一个只有声明和根节点的XML文档    
        /// </summary>    
        /// <param name="root"></param> 
        public void CreatXmlFile(string xmlPath, string xmlRoot)
        {
            //加入XML的声明段落graycode
            //xmlNode = xmlDoc.CreateNode(XmlNodeType.XmlDeclaration, "", ""); 
            XmlNode node = xmlDoc.CreateXmlDeclaration("1.0", "utf-8", "");
            xmlDoc.AppendChild(node);
            //加入一个根元素      
            XmlElement xmlElem = xmlDoc.CreateElement("", xmlRoot, "");
            xmlDoc.AppendChild(xmlElem);
            xmlDoc.Save(xmlPath);
            Dispose();
        }
        #endregion
          
        #region 在当前节点下插入一个空节点节点    
        /**//// <summary>    
        /// 在当前节点下插入一个空节点节点    
        /// </summary> 
        /// <param name="mainNode">当前节点路径</param>    
        /// <param name="node">节点名称</param>    
        public void CreatXmlNode(string mainNode, string node)    
        {      
            XmlNode MainNode = xmlDoc.SelectSingleNode(mainNode);      
            XmlElement objElem = xmlDoc.CreateElement(node);      
            MainNode.AppendChild(objElem);    
        }    
        #endregion    
        #region 在当前节点插入一个仅带值的节点    
        /**//// <summary>    
        /// 在当前节点插入一个仅带值的节点    
        /// </summary>    
        /// <param name="mainNode">当前节点</param>    
        /// <param name="node">新节点</param>    
        /// <param name="content">新节点值</param>    
        public void CreatXmlNode(string mainNode, string node, string content)    
        {      
            XmlNode MainNode = xmlDoc.SelectSingleNode(mainNode);      
            XmlElement objElem = xmlDoc.CreateElement(node);    
            objElem.InnerText = content;      
            MainNode.AppendChild(objElem);    
        }    
        #endregion    
        #region 在当前节点的插入一个仅带属性值的节点    
        /**//// <summary>    
        /// 在当前节点的插入一个仅带属性值的节点    
        /// </summary>    
        /// <param name="MainNode">当前节点或路径</param>    
        /// <param name="Node">新节点</param>    
        /// <param name="Attrib">新节点属性名称</param>    
        /// <param name="AttribValue">新节点属性值</param>    
        public void CreatXmlNode(string MainNode, string Node, string Attrib, string AttribValue)    
        {      
            XmlNode mainNode = xmlDoc.SelectSingleNode(MainNode);      
            XmlElement objElem = xmlDoc.CreateElement(Node);    
            objElem.SetAttribute(Attrib, AttribValue);      
            mainNode.AppendChild(objElem);    
        }    
        #endregion    
        #region 创建一个带属性值的节点值的节点    
        /**//// <summary>    
        /// 创建一个带属性值的节点值的节点    
        /// </summary>    
        /// <param name="MainNode">当前节点或路径</param> 
        /// <param name="Node">节点名称</param>    
        /// <param name="Attrib">属性名称</param>    
        /// <param name="AttribValue">属性值</param>    
        /// <param name="Content">节点传情</param>  
        public void CreatXmlNode(string MainNode, string Node, string Attrib, string AttribValue, string Content)    
        {      
            XmlNode mainNode = xmlDoc.SelectSingleNode(MainNode);      
            XmlElement objElem = xmlDoc.CreateElement(Node);      
            objElem.SetAttribute(Attrib, AttribValue);      
            objElem.InnerText = Content;      
            mainNode.AppendChild(objElem);   
        }   
        #endregion    
        
        #region 在当前节点的插入一个仅带n个属性值的节点
        public void CreatXmlNode(string MainNode, string Node, string []Attrib, string []AttribValue)
        {
            XmlNode mainNode = xmlDoc.SelectSingleNode(MainNode);
            XmlElement objElem = xmlDoc.CreateElement(Node);
            for (int i = 0; i < Attrib.Length; i++)
            {
                objElem.SetAttribute(Attrib[i], AttribValue[i]);
            }
            mainNode.AppendChild(objElem);
        }
        #endregion
        #region 在当前节点插入带n个属性的节点
        public void CreatXmlNode(string MainNode, string Node, string []Attrib, string []AttribValue,string Content)
        {
            XmlNode mainNode = xmlDoc.SelectSingleNode(MainNode);
            XmlElement objElem = xmlDoc.CreateElement(Node);
            for (int i = 0; i < Attrib.Length; i++)
            {
                objElem.SetAttribute(Attrib[i], AttribValue[i]);
            }
            objElem.InnerText = Content;
            mainNode.AppendChild(objElem);
        }
        #endregion  
          
        #region 根据父节点属性值读取子节点值
        /**/
        /**************************************************     
    * 函数名称:GetSubElementByAttribute(string XmlPath, string FatherElenetName, string AttributeName, int AttributeIndex, int ArrayLength)     
    * 功能说明:根据父节点属性值读取子节点值     
    * 参  数: XmlPath:xml路径;FatherElenetName:父节点名;AttributeName:属性值;AttributeIndex:属性索引;ArrayLength:要返回的节点数组长度     
    * 适应用Xml:     
    *      ArrayList al = new ArrayList();     
    *      al = XmlObject.GetSubElementByAttribute(XmlPath, "page", "/index.aspx", 0, 3);     
    *      for (int i = 0; i < al.Count; i++)     
    *      {     
    *        Response.Write(al[i].ToString());     
    *        Response.Write("<br>");     
    *      }     ************************************************/    
        /**//// <summary>    
        /// 根据父节点属性读取字节点值    
        /// </summary>    /
        // <param name="XmlPath">xml路径</param>    
        /// <param name="FatherElenetName">父节点名</param>    
        /// <param name="AttributeName">属性值</param>    
        /// <param name="AttributeIndex">属性索引</param>    
        /// <param name="ArrayLength">要返回的节点数组长度</param>    
        /// <returns></returns>    
        public static System.Collections.ArrayList GetSubElementByAttribute(string XmlPath, string FatherElenetName, string AttributeName, int AttributeIndex, int ArrayLength)    
        {      
            System.Collections.ArrayList al = new System.Collections.ArrayList();      
            XmlDocument docXml = new XmlDocument();      
            docXml.Load(@XmlPath);      
            XmlNodeList xn = docXml.DocumentElement.ChildNodes;      
            //遍历第一层节点      
            foreach (XmlElement element in xn)      
            {        
                //判断父节点是否为指定节点        
                if (element.Name == FatherElenetName)        
                {          
                    //判断父节点属性的索引是否大于指定索引          
                    if (element.Attributes.Count < AttributeIndex)            
                        return null;          
                    //判断父节点的属性值是否等于指定属性          
                    if (element.Attributes[AttributeIndex].Value == AttributeName)          
                    {            
                        XmlNodeList xx = element.ChildNodes;            
                        if (xx.Count > 0)            
                        {              
                            for (int i = 0; i < ArrayLength & i < xx.Count; i++)              
                            {                
                                al.Add(xx[i].InnerText);              
                            }            
                        }          
                    }        
                }      
            }      
            return al;    
        }    
        #endregion    
        #region 根据节点属性读取子节点值(较省资源模式)    
        /**//**************************************************     
        * 函数名称:GetSubElementByAttribute(string XmlPath, string FatherElement, string AttributeName, string AttributeValue, int ArrayLength)     
        * 功能说明:根据父节点属性值读取子节点值     
        * 参  数: XmlPath:xml路径;FatherElenetName:父节点名;AttributeName:属性名;AttributeValue:属性值;ArrayLength:要返回的节点数组长度     
        * 适应用Xml:     
        *      ArrayList al = new ArrayList();     
        *      al = XmlObject.GetSubElementByAttribute(XmlPath, "page", "@name", "/index.aspx", 3);     
        *      for (int i = 0; i < al.Count; i++)     
        *      {     
        *        Response.Write(al[i].ToString());     
        *        Response.Write("<br>");     
        *      }     
        ************************************************/    
        /**//// <summary>    
        /// 根据节点属性读取子节点值(较省资源模式)    
        /// </summary>    
        /// <param name="XmlPath">xml路径</param>    
        /// <param name="FatherElement">父节点值</param>    
        /// <param name="AttributeName">属性名称</param>    
        /// <param name="AttributeValue">属性值</param>    
        /// <param name="ArrayLength">返回的数组长度</param>    
        /// <returns></returns>    
        public static System.Collections.ArrayList GetSubElementByAttribute(string XmlPath, string FatherElement, string AttributeName, string AttributeValue, int ArrayLength)    
        {      
            System.Collections.ArrayList al = new System.Collections.ArrayList();      
            XmlDocument docXml = new XmlDocument();      
            docXml.Load(@XmlPath);      
            XmlNodeList xn;      
            xn = docXml.DocumentElement.SelectNodes("//" + FatherElement + "[" + @AttributeName + "='" + AttributeValue + "']");      
            XmlNodeList xx = xn.Item(0).ChildNodes;     
            for (int i = 0; i < ArrayLength & i < xx.Count; i++)      
            {        
                al.Add(xx.Item(i).InnerText);      
            }      
            return al;    
        }    
        #endregion
        #endregion

        #region 观测任务
        private string xFilePath="ObservationTasks.xml";
        public string xmlPath
        {
            get { return xFilePath; }
            set { xFilePath = value; }
        }
        private string xFileRoot = "ObsvTasks";
        public string xmlRoot
        {
            get { return xFileRoot; }
            set { xFileRoot = value; }
        }
        public void CreatXmlFileObsv()
        {
            CreatXmlFile(xmlPath, xmlRoot);
        }
        public int GetNodeNum(string xmlNode)
        {
            xmlDoc.Load(xmlPath);
            //XmlNodeList xn = xmlDoc.DocumentElement.ChildNodes;//一级节点可以用这个
            XmlNode objNode = xmlDoc.SelectSingleNode(xmlNode);
            XmlNodeList xn = objNode.ChildNodes;
            Dispose();
            return xn.Count;
        }
        public int GetTargetNum(string xmlRoot)
        {
            return GetNodeNum(xmlRoot);
        }
        public int GetCount()
        {
            return GetNodeNum(xmlRoot);
        }
        public int GetExposureNum(string Target)
        {
            Target=xmlRoot + "/" + Target;
            return GetNodeNum(Target);
        }
        public int GetAllElementCount()
        {
            int j = 0;
            xmlDoc.Load(xmlPath);
            //获取当前XML文档的根 一级
            XmlNode oNode = xmlDoc.DocumentElement;
            //获取根节点的所有子节点列表 
            XmlNodeList oList = oNode.ChildNodes;
            //遍历所有二级节点
            for (int i = 0; i < oList.Count; i++)
            {
                j += oList[i].ChildNodes.Count;
            }
            return j;
        }

        public void AddTargetExposure(string Number, string Frame, string Filter, string Duration, string Binning, string Repeat,string TargetName, string TargetRightAscension, string TargetDeclination)
        {
            xmlDoc.Load(xmlPath);
            XmlNode objNode = xmlDoc.SelectSingleNode(xmlRoot);
            XmlElement objElement = xmlDoc.CreateElement(Number);
            objElement.SetAttribute("Frame", Frame);
            objElement.SetAttribute("Filter", Filter);
            objElement.SetAttribute("Duration", Duration);
            objElement.SetAttribute("Binning", Binning);
            objElement.SetAttribute("Repeat", Repeat);
            objElement.SetAttribute("Name", TargetName);
            objElement.SetAttribute("RA", TargetRightAscension);
            objElement.SetAttribute("DEC", TargetDeclination);
            //objElement.InnerText = Content;
            objNode.AppendChild(objElement);
            xmlDoc.Save(xmlPath);
            Dispose();
        }

        public void AddTarget(string Target, string TargetName, string TargetRightAscension, string TargetDeclination)
        {
            xmlDoc.Load(xmlPath);
            XmlNode objNode = xmlDoc.SelectSingleNode(xmlRoot);
            XmlElement objElement = xmlDoc.CreateElement(Target);
            objElement.SetAttribute("Name", TargetName);
            objElement.SetAttribute("RA", TargetRightAscension);
            objElement.SetAttribute("DEC", TargetDeclination);
            //objElement.InnerText = Content;
            objNode.AppendChild(objElement);
            xmlDoc.Save(xmlPath);
            Dispose();
        }
        public void EditTarget(string Target, string TargetName, string TargetRightAscension, string TargetDeclination)
        {
            Target = xmlRoot + "/" + Target;
            xmlDoc.Load(xmlPath);
            XmlElement objElement = (XmlElement)xmlDoc.SelectSingleNode(Target);
            objElement.SetAttribute("Name", TargetName);
            objElement.SetAttribute("RA", TargetRightAscension);
            objElement.SetAttribute("DEC", TargetDeclination);
            //objElement.InnerText = Content;
            xmlDoc.Save(xmlPath);
            Dispose();
        } 
        public void DelTarget(string Target)
        {
            Target = xmlRoot + "/" + Target;
            xmlDoc.Load(xmlPath);
            string mainNode = Target.Substring(0, Target.LastIndexOf("/"));
            xmlDoc.SelectSingleNode(mainNode).RemoveChild(xmlDoc.SelectSingleNode(Target));
            xmlDoc.Save(xmlPath);
            Dispose();
        }
        public void AddExposure(string Target, string Exposure, string Frame, string Filter, string Duration, string Binning, string Repeat)
        {
            Target=xmlRoot + "/" + Target;
            xmlDoc.Load(xmlPath);
            XmlNode objNode = xmlDoc.SelectSingleNode(Target);
            XmlElement objElement = xmlDoc.CreateElement(Exposure);
            objElement.SetAttribute("Frame", Frame);
            objElement.SetAttribute("Filter", Filter);
            objElement.SetAttribute("Duration", Duration);
            objElement.SetAttribute("Binning", Binning);
            objElement.SetAttribute("Repeat", Repeat);
            //objElement.InnerText = Content;
            objNode.AppendChild(objElement);
            xmlDoc.Save(xmlPath);
            Dispose();
        }
        public void EditExposure(string Target, string Exposure, string Frame, string Filter, string Duration, string Binning, string Repeat)
        {
            Exposure = xmlRoot + "/" + Target + "/" + Exposure;
            xmlDoc.Load(xmlPath);
            XmlElement objElement = (XmlElement)xmlDoc.SelectSingleNode(Exposure);
            objElement.SetAttribute("Frame", Frame);
            objElement.SetAttribute("Filter", Filter);
            objElement.SetAttribute("Duration", Duration);
            objElement.SetAttribute("Binning", Binning);
            objElement.SetAttribute("Repeat", Repeat);
            //objElement.InnerText = Content;
            xmlDoc.Save(xmlPath);
            Dispose();
        }
        public void DelExposure(string Target, string Exposure)
        {
            Exposure = xmlRoot + "/" + Target + "/" + Exposure;
            xmlDoc.Load(xmlPath);
            string mainNode = Exposure.Substring(0, Exposure.LastIndexOf("/"));
            xmlDoc.SelectSingleNode(mainNode).RemoveChild(xmlDoc.SelectSingleNode(Exposure));
            xmlDoc.Save(xmlPath);
            Dispose();
        }
        public string[] GetExposureElement()
        {
            int k = GetCount()*8;
            string[] retstr = new string[k];
            xmlDoc.Load(xmlPath);
            //获取当前XML文档的根 一级
            XmlNode oNode = xmlDoc.DocumentElement;
            //获取根节点的所有子节点列表 
            XmlNodeList oList = oNode.ChildNodes;
            
            for (int i = 0; i < oList.Count; i++)
            {
                //二级
                retstr[i*8] = oList[i].Attributes[0].Value;
                retstr[i * 8 + 1] = oList[i].Attributes[1].Value;
                retstr[i * 8 + 2] = oList[i].Attributes[2].Value;
                retstr[i * 8 + 3] = oList[i].Attributes[3].Value;
                retstr[i * 8 + 4] = oList[i].Attributes[4].Value;
                retstr[i * 8 + 5] = oList[i].Attributes[5].Value;
                retstr[i * 8 + 6] = oList[i].Attributes[6].Value;
                retstr[i * 8 + 7] = oList[i].Attributes[7].Value;
            }
            return retstr;
        }
        /*
        public static System.Collections.ArrayList GetSubElementByAttribute(string XmlPath, string FatherElenetName, string AttributeName, int AttributeIndex, int ArrayLength)
        {
            System.Collections.ArrayList al = new System.Collections.ArrayList();
            XmlDocument docXml = new XmlDocument();
            docXml.Load(@XmlPath);
            XmlNodeList xn = docXml.DocumentElement.ChildNodes;
            //遍历第一层节点      
            foreach (XmlElement element in xn)
            {
                //判断父节点是否为指定节点        
                if (element.Name == FatherElenetName)
                {
                    //判断父节点属性的索引是否大于指定索引          
                    if (element.Attributes.Count < AttributeIndex)
                        return null;
                    //判断父节点的属性值是否等于指定属性          
                    if (element.Attributes[AttributeIndex].Value == AttributeName)
                    {
                        XmlNodeList xx = element.ChildNodes;
                        if (xx.Count > 0)
                        {
                            for (int i = 0; i < ArrayLength & i < xx.Count; i++)
                            {
                                al.Add(xx[i].InnerText);
                            }
                        }
                    }
                }
            }
            return al;
        } 
         * */
    #endregion

        #region 配置文件
        #endregion
    }
}
