/*
* 一元多项式的乘法与加法
*/
#include <iostream>
#include <list>

// 使用链表存储多项式

// 多项式每一项的结构
struct element
{
	int coefficient;
	int exponent;
};

void createInputPolynomials(std::list<element>& listA, std::list<element>& listB)
{
	int m, n = -1;
	std::cin >> m;

	for (int i = 0; i < m; i++)
	{
		element e;
		std::cin >> e.coefficient;
		std::cin >> e.exponent;
		if (e.coefficient != 0)
		{
			listA.push_back(e);
		}
	}
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		element e;
		std::cin >> e.coefficient;
		std::cin >> e.exponent;
		if (e.coefficient != 0)
		{
			listB.push_back(e);
		}
	}
}

std::list<element> addition(const std::list<element>& listA, const std::list<element>& listB)
{
	std::list<element> list_target;
	if (listA.empty() && (!listB.empty()))
	{
		list_target = listB;
	}
	else if (listB.empty() && (!listA.empty()))
	{
		list_target = listA;
	}
	else if (listA.empty() && listB.empty())
	{
		list_target.clear();
	}
	else
	{
		auto iterB = listB.cbegin();
		for (auto iterA = listA.cbegin(); iterA != listA.cend(); iterA++)
		{
			element current_A_element = *iterA;
			if (iterB == listB.cend())
			{
				// B链已处理完，则进行A链的拷贝
				element current_target_element;
				current_target_element.coefficient = current_A_element.coefficient;
				current_target_element.exponent = current_A_element.exponent;
				list_target.push_back(current_target_element);
				continue;
			}
			element current_B_element = *iterB;
			// 先处理B链中比A链当前项大的项
			while (current_A_element.exponent < current_B_element.exponent)
			{
				element current_target_element;
				current_target_element.coefficient = current_B_element.coefficient;
				current_target_element.exponent = current_B_element.exponent;
				list_target.push_back(current_target_element);
				iterB++;
				if (iterB == listB.cend())
				{
					// B链已处理完，则进行A链的拷贝
					element current_target_element;
					current_target_element.coefficient = current_A_element.coefficient;
					current_target_element.exponent = current_A_element.exponent;
					list_target.push_back(current_target_element);
					break;
				}
				else
				{
					current_B_element = *iterB;
				}
			}
			if (current_A_element.exponent == current_B_element.exponent) // A链当前项与B链当前项指数相等，相加后两边指针均前进
			{
				element current_target_element;
				current_target_element.coefficient = current_A_element.coefficient + current_B_element.coefficient;
				current_target_element.exponent = current_A_element.exponent;
				// if mereged sum == 0, skip
				if (current_target_element.coefficient != 0)
				{
					list_target.push_back(current_target_element);
				}
				iterB++; // 只有处理了B链中的项，B链指针才会往下移动
			}
			else if (current_A_element.exponent > current_B_element.exponent)
			{
				element current_target_element;
				current_target_element.coefficient = current_A_element.coefficient;
				current_target_element.exponent = current_A_element.exponent;
				list_target.push_back(current_target_element);
			}

		}
		while (iterB != listB.cend())
		{
			element current_target_element;
			element current_B_element = *iterB;
			current_target_element.coefficient = current_B_element.coefficient;
			current_target_element.exponent = current_B_element.exponent;
			list_target.push_back(current_target_element);
			iterB++;
		}
	}
	return list_target;
}

std::list<element> singleElementMultPolynomial(const element& ele, const std::list<element>& list)
{
	std::list<element> list_target;
	for (auto iter = list.cbegin(); iter != list.cend(); iter++)
	{
		element current_element;
		current_element.coefficient = (* iter).coefficient* ele.coefficient;
		// attention plz
		current_element.exponent = (*iter).exponent + ele.exponent;
		if (current_element.coefficient != 0)
		{
			list_target.push_back(current_element);
		}
	}
	return list_target;
}

std::list<element> multiplication(const std::list<element>& listA, const std::list<element>& listB)
{
	std::list<element> list_target;
	std::list<std::list<element>> sum_list;

	if (listA.empty() || listB.empty())
	{
		list_target.clear();
	}

	else
	{
		for (auto iterA = listA.cbegin(); iterA != listA.cend(); iterA++)
		{
			auto temp_list = singleElementMultPolynomial(*iterA, listB);
			sum_list.push_back(temp_list);
		}

		for (auto iter = sum_list.cbegin(); iter != sum_list.cend(); iter++)
		{
			if (iter == sum_list.cbegin())
			{
				list_target = *iter;
			}
			else
			{
				list_target = addition(list_target, *iter);
			}

		}
	}
	return list_target;
}



void output(std::list<element>& listMult, std::list<element>& listAdd)
{
	if (listMult.empty())
	{
		std::cout << "0 0";
	}
	else
	{
		for (auto iter = listMult.cbegin(); iter != listMult.cend(); iter++)
		{
			if (iter == listMult.cbegin())
			{
				std::cout << (*iter).coefficient << " " << (*iter).exponent;
			}
			else
			{
				std::cout << " " << (*iter).coefficient << " " << (*iter).exponent;
			}
		}
	}
	std::cout << std::endl;
	if (listAdd.empty())
	{
		std::cout << "0 0";
	}
	else
	{
		for (auto iter = listAdd.cbegin(); iter != listAdd.cend(); iter++)
		{
			if (iter == listAdd.cbegin())
			{
				std::cout << (*iter).coefficient << " " << (*iter).exponent;
			}
			else
			{
				std::cout << " " << (*iter).coefficient << " " << (*iter).exponent;
			}
		}
	}
}

int main()
{
	std::list<element> list_a;
	std::list<element> list_b;
	createInputPolynomials(list_a, list_b);
	auto list_add = addition(list_a, list_b);
	auto list_mult = multiplication(list_a, list_b);
	output(list_mult, list_add);

	return 0;
}
